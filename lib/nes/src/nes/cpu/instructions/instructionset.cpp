#include <nes/cpu/instructions/instructionset.h>

namespace nes::cpu::instructions
{
InstructionSet::InstructionSet(IInstructionErrorHandler& handler)
    : _adc(handler)
    , _and(handler)
    , _asl(handler)
    , _bcc(handler)
    , _bcs(handler)
    , _beq(handler)
    , _bit(handler)
    , _bmi(handler)
    , _bne(handler)
    , _bpl(handler)
    , _brk(handler)
    , _bvc(handler)
    , _bvs(handler)
    , _clc(handler)
    , _cld(handler)
    , _cli(handler)
    , _clv(handler)
    , _cmp(handler)
    , _cpx(handler)
    , _cpy(handler)
    , _dec(handler)
    , _dex(handler)
    , _dey(handler)
    , _eor(handler)
    , _inc(handler)
    , _inx(handler)
    , _iny(handler)
    , _jmp(handler)
    , _jsr(handler)
    , _lda(handler)
    , _ldx(handler)
    , _ldy(handler)
    , _lsr(handler)
    , _nop(handler)
    , _ora(handler)
    , _pha(handler)
    , _php(handler)
    , _pla(handler)
    , _plp(handler)
    , _rol(handler)
    , _ror(handler)
    , _rti(handler)
    , _rts(handler)
    , _sbc(handler)
    , _sec(handler)
    , _sed(handler)
    , _sei(handler)
    , _sta(handler)
    , _stx(handler)
    , _sty(handler)
    , _tax(handler)
    , _tay(handler)
    , _tsx(handler)
    , _txa(handler)
    , _txs(handler)
    , _tya(handler)
    , _unk("XXX", handler)
    , _instructionMatrix{
        &_brk, &_ora, &_unk, &_unk, &_unk, &_ora, &_asl, &_unk, &_php, &_ora, &_asl, &_unk, &_unk, &_ora, &_asl, &_unk,
        &_bpl, &_ora, &_unk, &_unk, &_unk, &_ora, &_asl, &_unk, &_clc, &_ora, &_unk, &_unk, &_unk, &_ora, &_asl, &_unk,
        &_jsr, &_and, &_unk, &_unk, &_bit, &_and, &_rol, &_unk, &_plp, &_and, &_rol, &_unk, &_bit, &_and, &_rol, &_unk, 
        &_bmi, &_and, &_unk, &_unk, &_unk, &_and, &_rol, &_unk, &_sec, &_and, &_unk, &_unk, &_unk, &_and, &_rol, &_unk, 
        &_rti, &_eor, &_unk, &_unk, &_unk, &_eor, &_lsr, &_unk, &_pha, &_eor, &_lsr, &_unk, &_jmp, &_eor, &_lsr, &_unk, 
        &_bvc, &_eor, &_unk, &_unk, &_unk, &_eor, &_lsr, &_unk, &_cli, &_eor, &_unk, &_unk, &_unk, &_eor, &_lsr, &_unk, 
        &_rts, &_adc, &_unk, &_unk, &_unk, &_adc, &_ror, &_unk, &_pla, &_adc, &_ror, &_unk, &_jmp, &_adc, &_ror, &_unk, 
        &_bvs, &_adc, &_unk, &_unk, &_unk, &_adc, &_ror, &_unk, &_sei, &_adc, &_unk, &_unk, &_unk, &_adc, &_ror, &_unk, 
        &_unk, &_sta, &_unk, &_unk, &_sty, &_sta, &_stx, &_unk, &_dey, &_unk, &_txa, &_unk, &_sty, &_sta, &_stx, &_unk, 
        &_bcc, &_sta, &_unk, &_unk, &_sty, &_sta, &_stx, &_unk, &_tya, &_sta, &_txs, &_unk, &_unk, &_sta, &_unk, &_unk, 
        &_ldy, &_lda, &_ldx, &_unk, &_ldy, &_lda, &_ldx, &_unk, &_tay, &_lda, &_tax, &_unk, &_ldy, &_lda, &_ldx, &_unk, 
        &_bcs, &_lda, &_unk, &_unk, &_ldy, &_lda, &_ldx, &_unk, &_clv, &_lda, &_tsx, &_unk, &_ldy, &_lda, &_ldx, &_unk, 
        &_cpy, &_cmp, &_unk, &_unk, &_cpy, &_cmp, &_dec, &_unk, &_iny, &_cmp, &_dex, &_unk, &_cpy, &_cmp, &_dec, &_unk, 
        &_bne, &_cmp, &_unk, &_unk, &_unk, &_cmp, &_dec, &_unk, &_cld, &_cmp, &_unk, &_unk, &_unk, &_cmp, &_dec, &_unk, 
        &_cpx, &_sbc, &_unk, &_unk, &_cpx, &_sbc, &_inc, &_unk, &_inx, &_sbc, &_nop, &_unk, &_cpx, &_sbc, &_inc, &_unk, 
        &_beq, &_sbc, &_unk, &_unk, &_unk, &_sbc, &_inc, &_unk, &_sed, &_sbc, &_unk, &_unk, &_unk, &_sbc, &_inc, &_unk, 
    }
{
}

}