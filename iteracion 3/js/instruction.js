class Instruction
{
    struct instruction 
    this.op = 0;
    this.r = 0;
    this.n = 0;
    this.d = 0;
    // Represents TAM instructions.
    op = 0;
    // OpCode
    r = 0;
    // RegisterNumber
    n = 0;
    // Length
    d = 0;
    // Operand
    write(output) throws IOException
    {
        output.writeInt(this.op);
        output.writeInt(this.r);
        output.writeInt(this.n);
        output.writeInt(this.d);
    }
    static read(input) throws IOException
    {
        var inst = new Instruction();
        try
        {
            inst.op = input.readInt();
            inst.r = input.readInt();
            inst.n = input.readInt();
            inst.d = input.readInt();
            return inst;
        } catch (var s = null)
        {
            return null;
        }
    }
}