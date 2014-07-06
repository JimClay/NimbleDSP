#include "RealVector.h"
#include "RealFirFilter.h"
#include "ComplexVector.h"

using namespace NimbleDSP;

const float F_S = 11025;
const int INTERP_FACTOR = 4;
const float MAX_FM_DEVIATION = 2.5e3;
const int BUF_LEN = 1024;
const float PI = 3.14159;


int main(int argc, char *argv[])
{
    FILE *audioInFile, *fmFile, *audioOutFile;
    
    // Get the data
    audioInFile = fopen("../../my_mule.raw", "rb");
    if (!audioInFile) {
        printf("%s: unable to open the audio input file\n", argv[0]);
        return 1;
    }
    
    fmFile = fopen("my_mule_fm.bin", "wb");
    if (!audioInFile) {
        printf("%s: unable to open the FM output file\n", argv[0]);
        return 1;
    }
    
    audioOutFile = fopen("my_mule_demod.bin", "wb");
    if (!audioInFile) {
        printf("%s: unable to open the audio output file\n", argv[0]);
        return 1;
    }

    // Interpolate to 44.1 kHz
    float filterTaps[] = {0.00705054, -0.00378462, -0.00578157, -0.00684215, -0.00517832, -0.00069077, 0.00466819, 0.00779634, 0.00630271, 0.00026491, -0.00728529, -0.01175208, -0.00964225, -0.00104201, 0.00978549, 0.01637187, 0.01379350, 0.00207902, -0.01294395, -0.02237565, -0.01935520, -0.00373854, 0.01675562, 0.03009996, 0.02678979, 0.00625119, -0.02147397, -0.04024787, -0.03694680, -0.01006288, 0.02750733, 0.05413949, 0.05141204, 0.01599806, -0.03577194, -0.07454949, -0.07366385, -0.02588230, 0.04851183, 0.10857881, 0.11306810, 0.04495870, -0.07288215, -0.18092434, -0.20631730, -0.09704051, 0.14898395, 0.47486202, 0.78207112, 0.96807523, 0.96807523, 0.78207112, 0.47486202, 0.14898395, -0.09704051, -0.20631730, -0.18092434, -0.07288215, 0.04495870, 0.11306810, 0.10857881, 0.04851183, -0.02588230, -0.07366385, -0.07454949, -0.03577194, 0.01599806, 0.05141204, 0.05413949, 0.02750733, -0.01006288, -0.03694680, -0.04024787, -0.02147397, 0.00625119, 0.02678979, 0.03009996, 0.01675562, -0.00373854, -0.01935520, -0.02237565, -0.01294395, 0.00207902, 0.01379350, 0.01637187, 0.00978549, -0.00104201, -0.00964225, -0.01175208, -0.00728529, 0.00026491, 0.00630271, 0.00779634, 0.00466819, -0.00069077, -0.00517832, -0.00684215, -0.00578157, -0.00378462, 0.00705054};
    NimbleDSP::RealFirFilter<float> filt(filterTaps, sizeof(filterTaps)/sizeof(filterTaps[0]));
    
    std::vector<float> scratchBufFloat;
    RealVector<float> buf(BUF_LEN, &scratchBufFloat);
    std::vector< std::complex<float> > scratchBufComplex;
    ComplexVector<float> complexBuf(BUF_LEN, &scratchBufComplex);
    
    int numSamps;
    float maxPhaseIncrement = 2 * PI * MAX_FM_DEVIATION / (F_S * INTERP_FACTOR);
    float lastPhase = 0;
    std::complex<float> lastAngle = 0;
    do {
        // Get the data
        numSamps = fread(VECTOR_TO_ARRAY(buf), sizeof(float), BUF_LEN, audioInFile);
        buf.resize(numSamps);
        
        // Interpolate to 44.1 kHz
        interp(buf, INTERP_FACTOR, filt);
        
        // FM modulate
        buf *= maxPhaseIncrement;                 // Convert amplitude to phase increment
        cumsum(buf, lastPhase);                   // Cumulatively sum the phase increments to get the actual phases
        lastPhase = buf[buf.size()-1];
        complexBuf = buf;
        complexBuf *= std::complex<float>(0, 1);  // Multiply by "j" (or "i", depending on your mathematical notation
        exp(complexBuf);                          // Calculate the exponential to frequency modulate
        
        fwrite(VECTOR_TO_ARRAY(complexBuf), sizeof(std::complex<float>), complexBuf.size(), fmFile);
        
        // Demodulate
        angle(complexBuf);                        // Calculate the phase
        std::complex<float> nextLastAngle = complexBuf[complexBuf.size()-1];
        diff(complexBuf, lastAngle);              // Phase difference (i.e. instantaneous frequency)
        lastAngle = nextLastAngle;
        // Handle any discontinuities that arise from -pi/+pi crossovers.
        for (unsigned i=0; i<complexBuf.size(); i++) {
            if (complexBuf[i].real() > PI) {
                complexBuf[i] -= 2 * PI;
            }
            else if (complexBuf[i].real() < -PI) {
                complexBuf[i] += 2 * PI;
            }
        }
        fwrite(VECTOR_TO_ARRAY(complexBuf), sizeof(std::complex<float>), complexBuf.size(), audioOutFile);
    } while (numSamps == BUF_LEN);
    
    fclose(audioInFile);
    fclose(fmFile);
    fclose(audioOutFile);
    
    return 0;
}
