#include "../core.h"
#include "../builtins.h"
#include "../nfns.h"


static NFnDesc* fun_invRegDesc;
static NFnDesc* fun_invSwapDesc;

B fun_invReg_c1(B t, B x) {
  B f = nfn_objU(t);
  return TI(f, fn_im)(f, x);
}
B fun_invReg_c2(B t, B w, B x) {
  B f = nfn_objU(t);
  return TI(f, fn_ix)(f, w, x);
}

B fun_invSwap_c1(B t, B x) {
  B f = nfn_objU(t);
  return TI(f, fn_is)(f, x);
}
B fun_invSwap_c2(B t, B w, B x) {
  B f = nfn_objU(t);
  return TI(f, fn_iw)(f, w, x);
}


B setInvReg_c1 (B t, B x) { rt_invFnReg  = x; return inc(bi_nativeInvReg); }
B setInvSwap_c1(B t, B x) { rt_invFnSwap = x; return inc(bi_nativeInvSwap); }
B nativeInvReg_c1(B t, B x) {
  if (isFun(x)) return m_nfn(fun_invRegDesc, x);
  return c1(rt_invFnReg, x);
}
B nativeInvSwap_c1(B t, B x) {
  if (isFun(x)) return m_nfn(fun_invSwapDesc, x);
  return c1(rt_invFnSwap, x);
}

void inverse_init() {
  fun_invRegDesc = registerNFn(m_str8l("(fun_invReg)"), fun_invReg_c1, fun_invReg_c2);
  fun_invSwapDesc = registerNFn(m_str8l("(fun_invSwap)"), fun_invSwap_c1, fun_invSwap_c2);
}