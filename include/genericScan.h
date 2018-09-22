#ifndef GENERICSCAN_H
#define GENERICSCAN_H

#include <stdarg.h>
#include <genericScan/export.h>
#include <genericStack.h>

/*************************
   Opaque object pointer
 *************************/
typedef struct genericScan genericScan_t;

/*************************
   Callback prototypes
 *************************/
typedef short (*genericScanStart_t)(void *userDatavp);
typedef short (*genericScanOpen_t)(void *userDatavp);
typedef short (*genericScanRead_t)(void *userDatavp);
typedef short (*genericScanClose_t)(void *userDatavp);
typedef short (*genericScanEnd_t)(void *userDatavp);

/*************************
   Option structure
 *************************/
typedef struct genericScanOption {
  genericScanStart_t startip;
  genericScanOpen_t  openip;
  genericScanRead_t  readip;
  genericScanClose_t closeip;
  genericScanEnd_t   endip;
} genericScanOption_t;

#ifdef _cpluscplus
extern "C" {
#endif
  /*************************
   Exported symbols
  *************************/
  genericScan_EXPORT const char               *genericScan_versions();
  genericScan_EXPORT genericScan_t            *genericScan_newp(void *userDatavp);
  genericScan_EXPORT void                      genericScan_freev(genericScan_t *genericScanp);
#ifdef _cpluscplus
}
#endif


#endif /* GENERICSCAN_H */
