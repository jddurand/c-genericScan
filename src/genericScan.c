#include <stdlib.h>
#include <errno.h>
#include <genericScan.h>
#include <genericStack.h>

/* We use internally a stack of genericScan_t objects */
struct genericScan {
  genericScanOption_t genericScanOption;
  short               genericStackb;         /* true genericStack when initialized */
  genericStack_t      _genericStack;
  genericStack_t     *genericStackp;         /* Shared between all objects */
  genericScan_t      *genericScanParentp;
};

static const char openc;
static const char closec;
static const void *opencp = &openc;
static const void *closecp = &closec;

/****************************************************************************/
const char *genericScan_versions()
/****************************************************************************/
{
  return GENERICSCAN_VERSION;
}

/****************************************************************************/
genericScan_t *genericScan_newp(genericScanOption_t *genericScanOptionp)
/****************************************************************************/
{
  genericScan_t *genericScanp = NULL;

  if (genericScanOptionp == NULL) {
    errno = EINVAL;
    goto err;
  }
  if ((genericScanOptionp->startip == NULL) ||
      (genericScanOptionp->openip == NULL) ||
      (genericScanOptionp->readip == NULL) ||
      (genericScanOptionp->closeip == NULL) ||
      (genericScanOptionp->endip == NULL)) {
    errno = EINVAL;
    goto err;
  }

  genericScanp = (genericScan_t *) malloc(sizeof(genericScan_t));
  if (genericScanp == NULL) {
    goto err;
  }

  genericScanp->genericScanOption  = *genericScanOptionp;
  genericScanp->genericStackb      = 0;
  genericScanp->genericStackp      = &(genericScanp->_genericStack);
  genericScanp->genericScanParentp = NULL;

  GENERICSTACK_INIT(genericScanp->genericStackp);
  if (GENERICSTACK_ERROR(genericScanp->genericStackp)) {
    goto err;
  }
  genericScanp->genericStackb       = 1;

  goto done;

 err:
  genericScan_freev(genericScanp);
  genericScanp = NULL;

 done:
  return genericScanp;
}

/****************************************************************************/
short genericScan_processi(genericScan_t *genericScanp)
/****************************************************************************/
{
  short               genericStackResetb = 0;
  short               rcb;
  void               *safeguardp;

  if (genericScanp == NULL) {
    errno = EINVAL;
    goto err;
  }

  if (! genericScanp->genericScanOption.startip(genericScanp->genericScanOption.userDatavp)) goto err;

  while(GENERICSTACK_USED(genericScanp->genericStackp) > 0) {
    /* First our safeguards */
    while(GENERICSTACK_USED(genericScanp->genericStackp) > 0) {
      safeguardp = GENERICSTACK_POP_PTR(genericScanp->genericStackp);
      if (safeguardp == opencp)  {
        genericScanp = (genericScan_t *) GENERICSTACK_POP_PTR(genericScanp->genericStackp);
        if (! genericScanp->genericScanOption.openip(genericScanp->genericScanOption.userDatavp)) {
          goto err;
        }
      }
      else if (safeguardp == closecp) {
        if (! genericScanp->genericScanOption.closeip(genericScanp->genericScanOption.userDatavp)) {
          goto err;
        }
        genericScanp = genericScanp->genericScanParentp;
      }
      else {
        break;
      }
    }

    /* Consumer's readip returns eventual inner content */
    if (! genericScanp->genericScanOption.readip(genericScanp->genericScanOption.userDatavp, &(genericScanp->genericScanParentp))) {
      goto err;
    }
    if (genericScanp->genericScanParentp != NULL) {
      /* Insert safeguards */
    }
  }
  
  rcb = 1;
  goto done;

 err:
  rcb = 0;

 done:
  return rcb; 
}


/****************************************************************************/
void genericScan_freev(genericScan_t *genericScanp)
/****************************************************************************/
{
  if (genericScanp != NULL) {
    if (genericScanp->genericStackb) {
      GENERICSTACK_RESET(genericScanp->genericStackp);
    }
    free(genericScanp);
  }
}

