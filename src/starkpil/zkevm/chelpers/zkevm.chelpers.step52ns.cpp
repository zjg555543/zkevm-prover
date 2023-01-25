#include "goldilocks_cubic_extension.hpp"
#include "zhInv.hpp"
#include "starks.hpp"
#include "constant_pols_starks.hpp"
#include "zkevmSteps.hpp"
#include "zkevm.chelpers.step52ns.hpp"
#define NR_ 4

/*
1. Provar amb 8
2. Challenges constants i amb Goldilocks
2. Treure conversions a Goldilocks3::Element
2.
*/

void ZkevmSteps::step52ns_first(StepsParams &params, uint64_t i)
{
     Goldilocks::Element tmp[NR_ * 3], tmp1[NR_ * 3], tmp2[NR_ * 3];

     Goldilocks3::mul0(tmp, &params.pols[12205424640 + i * 671], 671, (Goldilocks3::Element &)*params.challenges[5]);
     int i_args = 0;

     Goldilocks::Element *challenge5 = params.challenges[5];
     Goldilocks::Element *challenge6 = params.challenges[6];
     Goldilocks::Element challenge5_ops[3];
     Goldilocks::Element challenge6_ops[3];

     challenge5_ops[0] = challenge5[0] + challenge5[1];
     challenge5_ops[1] = challenge5[0] + challenge5[2];
     challenge5_ops[2] = challenge5[1] + challenge5[2];

     challenge6_ops[0] = challenge6[0] + challenge6[1];
     challenge6_ops[1] = challenge6[0] + challenge6[2];
     challenge6_ops[2] = challenge6[1] + challenge6[2];

     Goldilocks::Element *evals_ = params.evals[0];

     for (int kk = 0; kk < NOPS_; ++kk)
     {
          switch (op[kk])
          {
          case 1:
               Goldilocks3::mul1(tmp, tmp, challenge5, challenge5_ops);
               break;
          case 2:
               Goldilocks3::mul1(tmp, tmp, challenge6, challenge6_ops);
               break;
          case 3:
               Goldilocks3::mul1(tmp1, tmp, challenge5, challenge5_ops);
               break;
          case 4:
               Goldilocks3::mul1(tmp, tmp2, challenge6, challenge6_ops);
               break;
          case 5:
               Goldilocks3::mul2(tmp, tmp, params.xDivXSubXi[i]);
               break;
          case 6:
               Goldilocks3::mul2(tmp, tmp, params.xDivXSubWXi[i]);
               break;
          case 7:
               Goldilocks3::add0(tmp, tmp, tmp2);
               break;
          case 8:
               Goldilocks3::add0(tmp, tmp1, tmp);
               break;
          case 9:
               Goldilocks3::add1(tmp, tmp, &params.pols[args[i_args] + i * args[i_args + 1]], args[i_args + 1]);
               i_args += 2;
               break;
          case 10:
               Goldilocks3::add2(tmp, tmp, &params.pols[args[i_args] + i * args[i_args + 1]], args[i_args + 1]);
               i_args += 2;
               break;
          case 11:
               Goldilocks3::sub0(tmp2, &params.pols[args[i_args] + i * args[i_args + 1]], args[i_args + 1], &evals_[args[i_args + 2] * 3]);
               i_args += 3;
               break;
          case 12:
               Goldilocks3::sub2(tmp2, &params.pols[args[i_args] + i * args[i_args + 1]], args[i_args + 1], &evals_[args[i_args + 2] * 3]);
               i_args += 3;
               break;
          case 13:
               Goldilocks3::sub1(tmp2, &params.pConstPols2ns->getElement(args[i_args], i), params.pConstPols2ns->numPols(), &evals_[args[i_args + 1] * 3]);
               i_args += 2;
               break;
          case 14:
               Goldilocks3::sub1(tmp, &params.pConstPols2ns->getElement(5, i), params.pConstPols2ns->numPols(), evals_);
               break;
          case 15:
               Goldilocks3::mul1(tmp, tmp, challenge5, challenge5_ops);
               Goldilocks3::add2(tmp, tmp, &params.pols[args[i_args] + i * args[i_args + 1]], args[i_args + 1]);
               i_args += 2;
               break;
          case 16:
               Goldilocks3::mul1(tmp, tmp, challenge5, challenge5_ops);
               Goldilocks3::add1(tmp, tmp, &params.pols[args[i_args] + i * args[i_args + 1]], args[i_args + 1]);
               i_args += 2;
               break;
          case 17:
               Goldilocks3::sub0(tmp2, &params.pols[args[i_args] + i * args[i_args + 1]], args[i_args + 1], &evals_[args[i_args + 2] * 3]);
               Goldilocks3::mul1Add(tmp, tmp, challenge6, challenge6_ops, tmp2);
               // Goldilocks3::add0(tmp, tmp, tmp2);
               i_args += 3;
               break;
          case 18:
               Goldilocks3::sub1(tmp2, &params.pConstPols2ns->getElement(args[i_args], i), params.pConstPols2ns->numPols(), &evals_[args[i_args + 1] * 3]);
               Goldilocks3::mul1Add(tmp, tmp, challenge6, challenge6_ops, tmp2);
               // Goldilocks3::add0(tmp, tmp, tmp2);
               i_args += 2;
               break;
          case 19:
               Goldilocks3::sub2(tmp2, &params.pols[args[i_args] + i * args[i_args + 1]], args[i_args + 1], &evals_[args[i_args + 2] * 3]);
               Goldilocks3::mul1Add(tmp, tmp, challenge6, challenge6_ops, tmp2);
               // Goldilocks3::add0(tmp, tmp, tmp2);
               i_args += 3;
               break;
          default:
               std::cout << " Wrong operation in step52ns_first!" << std::endl;
               exit(1); // rick, use execption
          }
     }
     assert(i_args == NARGS_);
     Goldilocks3::copy_(&(params.f_2ns[i * 3]), tmp);
}

void ZkevmSteps::step52ns_i(StepsParams &params, uint64_t i)
{
}

void ZkevmSteps::step52ns_last(StepsParams &params, uint64_t i)
{
}