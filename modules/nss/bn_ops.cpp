#include <cryptofuzz/util.h>
#include <cryptofuzz/repository.h>
#include <fuzzing/datasource/id.hpp>

#include "bn_ops.h"

namespace cryptofuzz {
namespace module {
namespace NSS_bignum {

bool Add::Run(Datasource& ds, Bignum& res, std::vector<Bignum>& bn) const {
    (void)ds;
    bool ret = false;

    CF_CHECK_EQ(mp_add(bn[0].GetPtr(), bn[1].GetPtr(), res.GetPtr()), MP_OKAY);

    ret = true;

end:
    return ret;
}

bool Sub::Run(Datasource& ds, Bignum& res, std::vector<Bignum>& bn) const {
    (void)ds;
    bool ret = false;

    CF_CHECK_EQ(mp_sub(bn[0].GetPtr(), bn[1].GetPtr(), res.GetPtr()), MP_OKAY);

    ret = true;

end:
    return ret;
}

bool Mul::Run(Datasource& ds, Bignum& res, std::vector<Bignum>& bn) const {
    (void)ds;
    bool ret = false;

    CF_CHECK_EQ(mp_mul(bn[0].GetPtr(), bn[1].GetPtr(), res.GetPtr()), MP_OKAY);

    ret = true;

end:
    return ret;
}

bool Div::Run(Datasource& ds, Bignum& res, std::vector<Bignum>& bn) const {
    (void)ds;
    bool ret = false;

    CF_CHECK_EQ(mp_div(bn[0].GetPtr(), bn[1].GetPtr(), res.GetPtr(), nullptr), MP_OKAY);

    ret = true;

end:
    return ret;
}

bool Sqr::Run(Datasource& ds, Bignum& res, std::vector<Bignum>& bn) const {
    (void)ds;
    bool ret = false;

    CF_CHECK_EQ(mp_sqr(bn[0].GetPtr(), res.GetPtr()), MP_OKAY);

    ret = true;

end:
    return ret;
}

bool Mod::Run(Datasource& ds, Bignum& res, std::vector<Bignum>& bn) const {
    (void)ds;
    bool ret = false;

    CF_CHECK_EQ(mp_mod(bn[0].GetPtr(), bn[1].GetPtr(), res.GetPtr()), MP_OKAY);

    ret = true;

end:
    return ret;
}

bool ExpMod::Run(Datasource& ds, Bignum& res, std::vector<Bignum>& bn) const {
    (void)ds;
    bool ret = false;

    Bignum zero;
    mp_zero(zero.GetPtr());
    if ( mp_cmp(zero.GetPtr(), bn[0].GetPtr()) == 0 ) {
        goto end;
    }

    CF_CHECK_EQ(mp_exptmod(bn[0].GetPtr(), bn[1].GetPtr(), bn[2].GetPtr(), res.GetPtr()), MP_OKAY);

    ret = true;

end:
    return ret;
}

bool GCD::Run(Datasource& ds, Bignum& res, std::vector<Bignum>& bn) const {
    (void)ds;
    bool ret = false;

    CF_CHECK_EQ(mp_gcd(bn[0].GetPtr(), bn[1].GetPtr(), res.GetPtr()), MP_OKAY);

    ret = true;

end:
    return ret;
}

bool AddMod::Run(Datasource& ds, Bignum& res, std::vector<Bignum>& bn) const {
    (void)ds;
    bool ret = false;

    CF_CHECK_EQ(mp_addmod(bn[0].GetPtr(), bn[1].GetPtr(), bn[2].GetPtr(), res.GetPtr()), MP_OKAY);

    ret = true;

end:
    return ret;
}

bool SubMod::Run(Datasource& ds, Bignum& res, std::vector<Bignum>& bn) const {
    (void)ds;
    bool ret = false;

    CF_CHECK_EQ(mp_submod(bn[0].GetPtr(), bn[1].GetPtr(), bn[2].GetPtr(), res.GetPtr()), MP_OKAY);

    ret = true;

end:
    return ret;
}

bool MulMod::Run(Datasource& ds, Bignum& res, std::vector<Bignum>& bn) const {
    (void)ds;
    bool ret = false;

    CF_CHECK_EQ(mp_mulmod(bn[0].GetPtr(), bn[1].GetPtr(), bn[2].GetPtr(), res.GetPtr()), MP_OKAY);

    ret = true;

end:
    return ret;
}

bool SqrMod::Run(Datasource& ds, Bignum& res, std::vector<Bignum>& bn) const {
    (void)ds;
    bool ret = false;

    CF_CHECK_EQ(mp_sqrmod(bn[0].GetPtr(), bn[1].GetPtr(), res.GetPtr()), MP_OKAY);

    ret = true;

end:
    return ret;
}

bool InvMod::Run(Datasource& ds, Bignum& res, std::vector<Bignum>& bn) const {
    (void)ds;
    bool ret = false;

    CF_CHECK_EQ(mp_invmod(bn[0].GetPtr(), bn[1].GetPtr(), res.GetPtr()), MP_OKAY);

    ret = true;

end:
    return ret;
}

bool LCM::Run(Datasource& ds, Bignum& res, std::vector<Bignum>& bn) const {
    (void)ds;
    bool ret = false;

    CF_CHECK_EQ(mp_lcm(bn[0].GetPtr(), bn[1].GetPtr(), res.GetPtr()), MP_OKAY);

    ret = true;

end:
    return ret;
}

bool Cmp::Run(Datasource& ds, Bignum& res, std::vector<Bignum>& bn) const {
    (void)ds;

    res.Set( std::to_string(mp_cmp(bn[0].GetPtr(), bn[1].GetPtr())) );
    return true;
}

bool Abs::Run(Datasource& ds, Bignum& res, std::vector<Bignum>& bn) const {
    (void)ds;
    bool ret = false;

    CF_CHECK_EQ(mp_abs(bn[0].GetPtr(), res.GetPtr()), MP_OKAY);

    ret = true;

end:
    return ret;
}

bool Neg::Run(Datasource& ds, Bignum& res, std::vector<Bignum>& bn) const {
    (void)ds;
    bool ret = false;

    CF_CHECK_EQ(mp_neg(bn[0].GetPtr(), res.GetPtr()), MP_OKAY);

    ret = true;

end:
    return ret;
}

bool IsEven::Run(Datasource& ds, Bignum& res, std::vector<Bignum>& bn) const {
    (void)ds;
    (void)res;

    res.Set( std::to_string(mp_iseven(bn[0].GetPtr()) ? 1 : 0) );

    return true;
}

bool IsOdd::Run(Datasource& ds, Bignum& res, std::vector<Bignum>& bn) const {
    (void)ds;
    (void)res;

    res.Set( std::to_string(mp_isodd(bn[0].GetPtr()) ? 1 : 0) );

    return true;
}

} /* namespace NSS_bignum */
} /* namespace module */
} /* namespace cryptofuzz */
