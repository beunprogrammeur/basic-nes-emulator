#pragma once
#include <nes/cpu/instructions/instructions.h>
#include <nes/cpu/instructions/iinstructionset.h>

namespace nes::cpu::instructions
{
class InstructionSet : public IInstructionSet
{
private:
    ADCInstruction _adc;
    ANDInstruction _and;
    ASLInstruction _asl;
    BCCInstruction _bcc;
    BCSInstruction _bcs;
    BEQInstruction _beq;
    BITInstruction _bit;
    BMIInstruction _bmi;
    BNEInstruction _bne;
    BPLInstruction _bpl;
    BRKInstruction _brk;
    BVCInstruction _bvc;
    BVSInstruction _bvs;
    CLCInstruction _clc;
    CLDInstruction _cld;
    CLIInstruction _cli;
    CLVInstruction _clv;
    CMPInstruction _cmp;
    CPXInstruction _cpx;
    CPYInstruction _cpy;
    DECInstruction _dec;
    DEXInstruction _dex;
    DEYInstruction _dey;
    EORInstruction _eor;
    INCInstruction _inc;
    INXInstruction _inx;
    INYInstruction _iny;
    JMPInstruction _jmp;
    JSRInstruction _jsr;
    LDAInstruction _lda;
    LDXInstruction _ldx;
    LDYInstruction _ldy;
    LSRInstruction _lsr;
    NOPInstruction _nop;
    ORAInstruction _ora;
    PHAInstruction _pha;
    PHPInstruction _php;
    PLAInstruction _pla;
    PLPInstruction _plp;
    ROLInstruction _rol;
    RORInstruction _ror;
    RTIInstruction _rti;
    RTSInstruction _rts;
    SBCInstruction _sbc;
    SECInstruction _sec;
    SEDInstruction _sed;
    SEIInstruction _sei;
    STAInstruction _sta;
    STXInstruction _stx;
    STYInstruction _sty;
    TAXInstruction _tax;
    TAYInstruction _tay;
    TSXInstruction _tsx;
    TXAInstruction _txa;
    TXSInstruction _txs;
    TYAInstruction _tya;
    BaseInstruction _unk;
    BaseInstruction* _instructionMatrix[256];
    AddressingMode _addressingModeMatrix[256];
public:
    InstructionSet(IInstructionErrorHandler& handler);
    virtual IInstruction& get(const uint8_t index) override;
};
}