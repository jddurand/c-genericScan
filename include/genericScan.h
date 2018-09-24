#ifndef GENERICSCAN_H
#define GENERICSCAN_H

#include <stdarg.h>
#include <genericScan/export.h>

/*************************
   Opaque object pointer
 *************************/
typedef struct genericScan genericScan_t;

/*************************
   Forward declarations
 *************************/
typedef struct genericScanOption genericScanOption_t;

/*************************
   Callback prototypes
 *************************/
typedef short (*genericScanStart_t)(void *userDatavp);
typedef short (*genericScanOpen_t)(void *userDatavp);
typedef short (*genericScanRead_t)(void *userDatavp, genericScan_t **genericScanInnerpp);
typedef short (*genericScanClose_t)(void *userDatavp);
typedef short (*genericScanEnd_t)(void *userDatavp);

/*************************
   Option structure
 *************************/
struct genericScanOption {
  void              *userDatavp;
  genericScanStart_t startip;
  genericScanOpen_t  openip;
  genericScanRead_t  readip;
  genericScanClose_t closeip;
  genericScanEnd_t   endip;
};

#ifdef _cpluscplus
extern "C" {
#endif
  /*************************
   Exported symbols
  *************************/
  genericScan_EXPORT const char               *genericScan_versions();
  genericScan_EXPORT genericScan_t            *genericScan_newp(genericScanOption_t *genericScanOptionp);
  genericScan_EXPORT short                     genericScan_processi(genericScan_t *genericScanp);
  genericScan_EXPORT void                      genericScan_freev(genericScan_t *genericScanp);
#ifdef _cpluscplus
}
#endif


#endif /* GENERICSCAN_H */
