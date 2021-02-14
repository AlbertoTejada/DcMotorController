#ifndef _ENCODERS_H_
#define _ENCODERS_H_

#define ENCODER1_PIN (2U)
#define ENCODER2_PIN (3U)


#if defined(__cplusplus)
extern "C" {
#endif

void Encoders_Init(void);

void Encoders_Interruption();

void Encoders_Main();

void Encoders_WriteOutputs();

void Encoders_Task();

#if defined(__cplusplus)
} // Closing brace for extern C
#endif

#endif // _ENCODERS_H_

