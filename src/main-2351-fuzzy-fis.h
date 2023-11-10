#include "Arduino.h"

#define FIS_TYPE float
#define FIS_RESOLUSION 101
#define FIS_MIN -3.4028235E+38
#define FIS_MAX 3.4028235E+38

typedef FIS_TYPE (*_FIS_MF)(FIS_TYPE, FIS_TYPE *);
typedef FIS_TYPE (*_FIS_ARR_OP)(FIS_TYPE, FIS_TYPE);
typedef FIS_TYPE (*_FIS_ARR)(FIS_TYPE *, int, _FIS_ARR_OP);

/* variables */

extern unsigned int __bss_end;
extern unsigned int __heap_start;
extern void *__brkval;

const int fis_gcI = 4;
const int fis_gcO = 2;
const int fis_gcR = 18;

FIS_TYPE g_fisInput[fis_gcI];
FIS_TYPE g_fisOutput[fis_gcO];

/* function */

int freeMemory() {
    int free_memory;

    if ((int) __brkval == 0)
        free_memory = ((int) &free_memory) - ((int) &__bss_end);
    else
        free_memory = ((int) &free_memory) - ((int) __brkval);

    return free_memory;
}

FIS_TYPE mapF(FIS_TYPE value, FIS_TYPE fromLow, FIS_TYPE fromHigh, FIS_TYPE toLow, FIS_TYPE toHigh) {
    return (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
}

FIS_TYPE fis_trapmf(FIS_TYPE x, FIS_TYPE *p) {
    FIS_TYPE a = p[0], b = p[1], c = p[2], d = p[3];
    FIS_TYPE t1 = ((x <= c) ? 1 : ((d < x) ? 0 : ((c != d) ? ((d - x) / (d - c)) : 0)));
    FIS_TYPE t2 = ((b <= x) ? 1 : ((x < a) ? 0 : ((a != b) ? ((x - a) / (b - a)) : 0)));
    return (FIS_TYPE) min(t1, t2);
}

FIS_TYPE fis_prod(FIS_TYPE a, FIS_TYPE b) {
    return (a * b);
}

FIS_TYPE fis_probor(FIS_TYPE a, FIS_TYPE b) {
    return (a + b - (a * b));
}

FIS_TYPE fis_sum(FIS_TYPE a, FIS_TYPE b) {
    return (a + b);
}

FIS_TYPE fis_array_operation(FIS_TYPE *array, int size, _FIS_ARR_OP pfnOp) {
    int i;
    FIS_TYPE ret = 0;

    if (size == 0) return ret;
    if (size == 1) return array[0];

    ret = array[0];
    for (i = 1; i < size; i++) {
        ret = (*pfnOp)(ret, array[i]);
    }

    return ret;
}

_FIS_MF fis_gMF[] = {
        fis_trapmf
};

int fis_gIMFCount[] = {2, 2, 2, 2};

int fis_gOMFCount[] = {3, 3};

FIS_TYPE fis_gMFI0Coeff1[] = {0, 0, 40, 60};
FIS_TYPE fis_gMFI0Coeff2[] = {40, 60, 100, 100};
FIS_TYPE *fis_gMFI0Coeff[] = {fis_gMFI0Coeff1, fis_gMFI0Coeff2};
FIS_TYPE fis_gMFI1Coeff1[] = {0, 0, 40, 60};
FIS_TYPE fis_gMFI1Coeff2[] = {40, 60, 100, 100};
FIS_TYPE *fis_gMFI1Coeff[] = {fis_gMFI1Coeff1, fis_gMFI1Coeff2};
FIS_TYPE fis_gMFI2Coeff1[] = {0, 0, 40, 60};
FIS_TYPE fis_gMFI2Coeff2[] = {40, 60, 100, 100};
FIS_TYPE *fis_gMFI2Coeff[] = {fis_gMFI2Coeff1, fis_gMFI2Coeff2};
FIS_TYPE fis_gMFI3Coeff1[] = {0, 0, 40, 60};
FIS_TYPE fis_gMFI3Coeff2[] = {40, 60, 100, 100};
FIS_TYPE *fis_gMFI3Coeff[] = {fis_gMFI3Coeff1, fis_gMFI3Coeff2};
FIS_TYPE **fis_gMFICoeff[] = {fis_gMFI0Coeff, fis_gMFI1Coeff, fis_gMFI2Coeff, fis_gMFI3Coeff};

FIS_TYPE fis_gMFO0Coeff1[] = {0, 0, 0, 0, 0};
FIS_TYPE fis_gMFO0Coeff2[] = {0, 0, 0, 0, 0.5};
FIS_TYPE fis_gMFO0Coeff3[] = {0, 0, 0, 0, 1};
FIS_TYPE *fis_gMFO0Coeff[] = {fis_gMFO0Coeff1, fis_gMFO0Coeff2, fis_gMFO0Coeff3};
FIS_TYPE fis_gMFO1Coeff1[] = {0, 0, 0, 0, 0};
FIS_TYPE fis_gMFO1Coeff2[] = {0, 0, 0, 0, 0.5};
FIS_TYPE fis_gMFO1Coeff3[] = {0, 0, 0, 0, 1};
FIS_TYPE *fis_gMFO1Coeff[] = {fis_gMFO1Coeff1, fis_gMFO1Coeff2, fis_gMFO1Coeff3};
FIS_TYPE **fis_gMFOCoeff[] = {fis_gMFO0Coeff, fis_gMFO1Coeff};

int fis_gMFI0[] = {0, 0};
int fis_gMFI1[] = {0, 0};
int fis_gMFI2[] = {0, 0};
int fis_gMFI3[] = {0, 0};
int *fis_gMFI[] = {fis_gMFI0, fis_gMFI1, fis_gMFI2, fis_gMFI3};

int *fis_gMFO[] = {};

FIS_TYPE fis_gRWeight[] = {1, 1, 1, 1, 1, 1, 1, 1};

int fis_gRType[] = {1, 1, 1, 1, 1, 1, 1, 1};

int fis_gRI0[] = {1, 1, 0, 0};
int fis_gRI1[] = {1, 2, 0, 0};
int fis_gRI2[] = {2, 1, 0, 0};
int fis_gRI3[] = {2, 2, 0, 0};
int fis_gRI4[] = {0, 0, 1, 1};
int fis_gRI5[] = {0, 0, 1, 2};
int fis_gRI6[] = {0, 0, 2, 1};
int fis_gRI7[] = {0, 0, 2, 2};
int *fis_gRI[] = {fis_gRI0, fis_gRI1, fis_gRI2, fis_gRI3, fis_gRI4, fis_gRI5, fis_gRI6, fis_gRI7};

int fis_gRO0[] = {2, 0};
int fis_gRO1[] = {3, 0};
int fis_gRO2[] = {1, 0};
int fis_gRO3[] = {2, 0};
int fis_gRO4[] = {0, 2};
int fis_gRO5[] = {0, 3};
int fis_gRO6[] = {0, 1};
int fis_gRO7[] = {0, 2};
int *fis_gRO[] = {fis_gRO0, fis_gRO1, fis_gRO2, fis_gRO3, fis_gRO4, fis_gRO5, fis_gRO6, fis_gRO7};

FIS_TYPE fis_gIMin[] = {0, 0, 0, 0};

FIS_TYPE fis_gIMax[] = {100, 100, 100, 100};

FIS_TYPE fis_gOMin[] = {0, 0};

FIS_TYPE fis_gOMax[] = {1, 1};

void fis_evaluate() {
    FIS_TYPE fuzzyInput0[] = {0, 0};
    FIS_TYPE fuzzyInput1[] = {0, 0};
    FIS_TYPE fuzzyInput2[] = {0, 0};
    FIS_TYPE fuzzyInput3[] = {0, 0};
    FIS_TYPE *fuzzyInput[fis_gcI] = {
            fuzzyInput0,
            fuzzyInput1,
            fuzzyInput2,
            fuzzyInput3,
    };
    FIS_TYPE fuzzyOutput0[] = {0, 0, 0};
    FIS_TYPE fuzzyOutput1[] = {0, 0, 0};
    FIS_TYPE *fuzzyOutput[fis_gcO] = {
            fuzzyOutput0,
            fuzzyOutput1,
    };
    FIS_TYPE fuzzyRules[fis_gcR] = {0};
    FIS_TYPE fuzzyFires[fis_gcR] = {0};
    FIS_TYPE *fuzzyRuleSet[] = {fuzzyRules, fuzzyFires};
    FIS_TYPE sW = 0;

    int i, j, r, o;
    for (i = 0; i < fis_gcI; ++i) {
        for (j = 0; j < fis_gIMFCount[i]; ++j) {
            fuzzyInput[i][j] =
                    (fis_gMF[fis_gMFI[i][j]])(g_fisInput[i], fis_gMFICoeff[i][j]);
        }
    }

    int index = 0;
    for (r = 0; r < fis_gcR; ++r) {
        if (fis_gRType[r] == 1) {
            fuzzyFires[r] = 1;
            for (i = 0; i < fis_gcI; ++i) {
                index = fis_gRI[r][i];
                if (index > 0)
                    fuzzyFires[r] = fis_prod(fuzzyFires[r], fuzzyInput[i][index - 1]);
                else if (index < 0)
                    fuzzyFires[r] = fis_prod(fuzzyFires[r], 1 - fuzzyInput[i][-index - 1]);
                else
                    fuzzyFires[r] = fis_prod(fuzzyFires[r], 1);
            }
        } else {
            fuzzyFires[r] = 0;
            for (i = 0; i < fis_gcI; ++i) {
                index = fis_gRI[r][i];
                if (index > 0)
                    fuzzyFires[r] = fis_probor(fuzzyFires[r], fuzzyInput[i][index - 1]);
                else if (index < 0)
                    fuzzyFires[r] = fis_probor(fuzzyFires[r], 1 - fuzzyInput[i][-index - 1]);
                else
                    fuzzyFires[r] = fis_probor(fuzzyFires[r], 0);
            }
        }

        fuzzyFires[r] = fis_gRWeight[r] * fuzzyFires[r];
        sW += fuzzyFires[r];
    }

    if (sW == 0) {
        for (o = 0; o < fis_gcO; ++o) {
            g_fisOutput[o] = ((fis_gOMax[o] + fis_gOMin[o]) / 2);
        }
    } else {
        for (o = 0; o < fis_gcO; ++o) {
            FIS_TYPE sWI = 0.0;
            for (j = 0; j < fis_gOMFCount[o]; ++j) {
                fuzzyOutput[o][j] = fis_gMFOCoeff[o][j][fis_gcI];
                for (i = 0; i < fis_gcI; ++i) {
                    fuzzyOutput[o][j] += g_fisInput[i] * fis_gMFOCoeff[o][j][i];
                }
            }

            for (r = 0; r < fis_gcR; ++r) {
                index = fis_gRO[r][o] - 1;
                sWI += fuzzyFires[r] * fuzzyOutput[o][index];
            }

            g_fisOutput[o] = sWI / sW;
        }
    }
}

// FIS_TYPE fis_trapmf(FIS_TYPE x, FIS_TYPE* p) {
//   FIS_TYPE a = p[0], b = p[1], c = p[2], d = p[3];
//   FIS_TYPE t1 = ((x <= c) ? 1 : ((d < x) ? 0 : ((c != d) ? ((d - x) / (d - c)) : 0)));
//   FIS_TYPE t2 = ((b <= x) ? 1 : ((x < a) ? 0 : ((a != b) ? ((x - a) / (b - a)) : 0)));
//   return (FIS_TYPE)min(t1, t2);
// }

// FIS_TYPE fis_trimf(FIS_TYPE x, FIS_TYPE* p) {
//   FIS_TYPE a = p[0], b = p[1], c = p[2];
//   FIS_TYPE t1 = (x - a) / (b - a);
//   FIS_TYPE t2 = (c - x) / (c - b);
//   if ((a == b) && (b == c)) return (FIS_TYPE)(x == a);
//   if (a == b) return (FIS_TYPE)(t2 * (b <= x) * (x <= c));
//   if (b == c) return (FIS_TYPE)(t1 * (a <= x) * (x <= b));
//   t1 = min(t1, t2);
//   return (FIS_TYPE)max(t1, 0);
// }

// FIS_TYPE fis_prod(FIS_TYPE a, FIS_TYPE b) {
//   return (a * b);
// }

// FIS_TYPE fis_probor(FIS_TYPE a, FIS_TYPE b) {
//   return (a + b - (a * b));
// }

// FIS_TYPE fis_sum(FIS_TYPE a, FIS_TYPE b) {
//   return (a + b);
// }

// FIS_TYPE fis_array_operation(FIS_TYPE* array, int size, _FIS_ARR_OP pfnOp) {
//   int i;
//   FIS_TYPE ret = 0;

//   if (size == 0) return ret;
//   if (size == 1) return array[0];

//   ret = array[0];
//   for (i = 1; i < size; i++) {
//     ret = (*pfnOp)(ret, array[i]);
//   }

//   return ret;
// }

// _FIS_MF fis_gMF[] = {
//   fis_trapmf, fis_trimf
// };

// int fis_gIMFCount[] = { 3, 3, 3, 3 };
// int fis_gOMFCount[] = { 3, 3 };

// FIS_TYPE fis_gMFI0Coeff1[] = { 0, 0, 20, 40 };
// FIS_TYPE fis_gMFI0Coeff2[] = { 30, 50, 70 };
// FIS_TYPE fis_gMFI0Coeff3[] = { 60, 80, 100, 100 };
// FIS_TYPE* fis_gMFI0Coeff[] = { fis_gMFI0Coeff1, fis_gMFI0Coeff2, fis_gMFI0Coeff3 };
// FIS_TYPE fis_gMFI1Coeff1[] = { 0, 0, 20, 40 };
// FIS_TYPE fis_gMFI1Coeff2[] = { 30, 50, 70 };
// FIS_TYPE fis_gMFI1Coeff3[] = { 60, 80, 100, 100 };
// FIS_TYPE* fis_gMFI1Coeff[] = { fis_gMFI1Coeff1, fis_gMFI1Coeff2, fis_gMFI1Coeff3 };
// FIS_TYPE fis_gMFI2Coeff1[] = { 0, 0, 20, 40 };
// FIS_TYPE fis_gMFI2Coeff2[] = { 30, 50, 70 };
// FIS_TYPE fis_gMFI2Coeff3[] = { 60, 80, 100, 100 };
// FIS_TYPE* fis_gMFI2Coeff[] = { fis_gMFI2Coeff1, fis_gMFI2Coeff2, fis_gMFI2Coeff3 };
// FIS_TYPE fis_gMFI3Coeff1[] = { 0, 0, 20, 40 };
// FIS_TYPE fis_gMFI3Coeff2[] = { 30, 50, 70 };
// FIS_TYPE fis_gMFI3Coeff3[] = { 60, 80, 100, 100 };
// FIS_TYPE* fis_gMFI3Coeff[] = { fis_gMFI3Coeff1, fis_gMFI3Coeff2, fis_gMFI3Coeff3 };
// FIS_TYPE** fis_gMFICoeff[] = { fis_gMFI0Coeff, fis_gMFI1Coeff, fis_gMFI2Coeff, fis_gMFI3Coeff };

// FIS_TYPE fis_gMFO0Coeff1[] = { 0, 0, 0, 0, 0 };
// FIS_TYPE fis_gMFO0Coeff2[] = { 0, 0, 0, 0, 0.5 };
// FIS_TYPE fis_gMFO0Coeff3[] = { 0, 0, 0, 0, 1 };
// FIS_TYPE* fis_gMFO0Coeff[] = { fis_gMFO0Coeff1, fis_gMFO0Coeff2, fis_gMFO0Coeff3 };
// FIS_TYPE fis_gMFO1Coeff1[] = { 0, 0, 0, 0, 0 };
// FIS_TYPE fis_gMFO1Coeff2[] = { 0, 0, 0, 0, 0.5 };
// FIS_TYPE fis_gMFO1Coeff3[] = { 0, 0, 0, 0, 1 };
// FIS_TYPE* fis_gMFO1Coeff[] = { fis_gMFO1Coeff1, fis_gMFO1Coeff2, fis_gMFO1Coeff3 };
// FIS_TYPE** fis_gMFOCoeff[] = { fis_gMFO0Coeff, fis_gMFO1Coeff };

// int fis_gMFI0[] = { 0, 1, 0 };
// int fis_gMFI1[] = { 0, 1, 0 };
// int fis_gMFI2[] = { 0, 1, 0 };
// int fis_gMFI3[] = { 0, 1, 0 };
// int* fis_gMFI[] = { fis_gMFI0, fis_gMFI1, fis_gMFI2, fis_gMFI3 };

// int* fis_gMFO[] = {};

// FIS_TYPE fis_gRWeight[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

// int fis_gRType[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

// int fis_gRI0[] = { 1, 1, 0, 0 };
// int fis_gRI1[] = { 1, 2, 0, 0 };
// int fis_gRI2[] = { 1, 3, 0, 0 };
// int fis_gRI3[] = { 2, 1, 0, 0 };
// int fis_gRI4[] = { 2, 2, 0, 0 };
// int fis_gRI5[] = { 2, 3, 0, 0 };
// int fis_gRI6[] = { 3, 1, 0, 0 };
// int fis_gRI7[] = { 3, 2, 0, 0 };
// int fis_gRI8[] = { 3, 3, 0, 0 };
// int fis_gRI9[] = { 0, 0, 1, 1 };
// int fis_gRI10[] = { 0, 0, 1, 2 };
// int fis_gRI11[] = { 0, 0, 1, 3 };
// int fis_gRI12[] = { 0, 0, 2, 1 };
// int fis_gRI13[] = { 0, 0, 2, 2 };
// int fis_gRI14[] = { 0, 0, 2, 3 };
// int fis_gRI15[] = { 0, 0, 3, 1 };
// int fis_gRI16[] = { 0, 0, 3, 2 };
// int fis_gRI17[] = { 0, 0, 3, 3 };
// int* fis_gRI[] = { fis_gRI0, fis_gRI1, fis_gRI2, fis_gRI3, fis_gRI4, fis_gRI5, fis_gRI6, fis_gRI7, fis_gRI8, fis_gRI9, fis_gRI10, fis_gRI11, fis_gRI12, fis_gRI13, fis_gRI14, fis_gRI15, fis_gRI16, fis_gRI17 };

// int fis_gRO0[] = { 2, 0 };
// int fis_gRO1[] = { 3, 0 };
// int fis_gRO2[] = { 3, 0 };
// int fis_gRO3[] = { 1, 0 };
// int fis_gRO4[] = { 2, 0 };
// int fis_gRO5[] = { 3, 0 };
// int fis_gRO6[] = { 1, 0 };
// int fis_gRO7[] = { 1, 0 };
// int fis_gRO8[] = { 2, 0 };
// int fis_gRO9[] = { 0, 2 };
// int fis_gRO10[] = { 0, 3 };
// int fis_gRO11[] = { 0, 3 };
// int fis_gRO12[] = { 0, 1 };
// int fis_gRO13[] = { 0, 2 };
// int fis_gRO14[] = { 0, 3 };
// int fis_gRO15[] = { 0, 1 };
// int fis_gRO16[] = { 0, 1 };
// int fis_gRO17[] = { 0, 2 };
// int* fis_gRO[] = { fis_gRO0, fis_gRO1, fis_gRO2, fis_gRO3, fis_gRO4, fis_gRO5, fis_gRO6, fis_gRO7, fis_gRO8, fis_gRO9, fis_gRO10, fis_gRO11, fis_gRO12, fis_gRO13, fis_gRO14, fis_gRO15, fis_gRO16, fis_gRO17 };

// FIS_TYPE fis_gIMin[] = { 0, 0, 0, 0 };

// FIS_TYPE fis_gIMax[] = { 100, 100, 100, 100 };

// FIS_TYPE fis_gOMin[] = { 0, 0 };

// FIS_TYPE fis_gOMax[] = { 1, 1 };

// void fis_evaluate() {
//   FIS_TYPE fuzzyInput0[] = { 0, 0, 0 };
//   FIS_TYPE fuzzyInput1[] = { 0, 0, 0 };
//   FIS_TYPE fuzzyInput2[] = { 0, 0, 0 };
//   FIS_TYPE fuzzyInput3[] = { 0, 0, 0 };
//   FIS_TYPE* fuzzyInput[fis_gcI] = {
//     fuzzyInput0,
//     fuzzyInput1,
//     fuzzyInput2,
//     fuzzyInput3,
//   };
//   FIS_TYPE fuzzyOutput0[] = { 0, 0, 0 };
//   FIS_TYPE fuzzyOutput1[] = { 0, 0, 0 };
//   FIS_TYPE* fuzzyOutput[fis_gcO] = {
//     fuzzyOutput0,
//     fuzzyOutput1,
//   };
//   FIS_TYPE fuzzyRules[fis_gcR] = { 0 };
//   FIS_TYPE fuzzyFires[fis_gcR] = { 0 };
//   FIS_TYPE* fuzzyRuleSet[] = { fuzzyRules, fuzzyFires };
//   FIS_TYPE sW = 0;

//   int i, j, r, o;
//   for (i = 0; i < fis_gcI; ++i) {
//     for (j = 0; j < fis_gIMFCount[i]; ++j) {
//       fuzzyInput[i][j] =
//         (fis_gMF[fis_gMFI[i][j]])(g_fisInput[i], fis_gMFICoeff[i][j]);
//     }
//   }

//   int index = 0;
//   for (r = 0; r < fis_gcR; ++r) {
//     if (fis_gRType[r] == 1) {
//       fuzzyFires[r] = 1;
//       for (i = 0; i < fis_gcI; ++i) {
//         index = fis_gRI[r][i];
//         if (index > 0)
//           fuzzyFires[r] = fis_prod(fuzzyFires[r], fuzzyInput[i][index - 1]);
//         else if (index < 0)
//           fuzzyFires[r] = fis_prod(fuzzyFires[r], 1 - fuzzyInput[i][-index - 1]);
//         else
//           fuzzyFires[r] = fis_prod(fuzzyFires[r], 1);
//       }
//     } else {
//       fuzzyFires[r] = 0;
//       for (i = 0; i < fis_gcI; ++i) {
//         index = fis_gRI[r][i];
//         if (index > 0)
//           fuzzyFires[r] = fis_probor(fuzzyFires[r], fuzzyInput[i][index - 1]);
//         else if (index < 0)
//           fuzzyFires[r] = fis_probor(fuzzyFires[r], 1 - fuzzyInput[i][-index - 1]);
//         else
//           fuzzyFires[r] = fis_probor(fuzzyFires[r], 0);
//       }
//     }

//     fuzzyFires[r] = fis_gRWeight[r] * fuzzyFires[r];
//     sW += fuzzyFires[r];
//   }

//   if (sW == 0) {
//     for (o = 0; o < fis_gcO; ++o) {
//       g_fisOutput[o] = ((fis_gOMax[o] + fis_gOMin[o]) / 2);
//     }
//   } else {
//     for (o = 0; o < fis_gcO; ++o) {
//       FIS_TYPE sWI = 0.0;
//       for (j = 0; j < fis_gOMFCount[o]; ++j) {
//         fuzzyOutput[o][j] = fis_gMFOCoeff[o][j][fis_gcI];
//         for (i = 0; i < fis_gcI; ++i) {
//           fuzzyOutput[o][j] += g_fisInput[i] * fis_gMFOCoeff[o][j][i];
//         }
//       }

//       for (r = 0; r < fis_gcR; ++r) {
//         index = fis_gRO[r][o] - 1;
//         sWI += fuzzyFires[r] * fuzzyOutput[o][index];
//       }

//       g_fisOutput[o] = sWI / sW;
//     }
//   }
// }
