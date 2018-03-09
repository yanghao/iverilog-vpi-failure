// D flip-flop
module x(
input wire d,
input wire clk,
output reg q,
output reg q_bar
);

/*
input d, clk;
output q, q_bar;

wire d, clk;
reg q, q_bar;
*/

always @ (posedge clk)
begin
    q <= d;
    q_bar <= !d;
end

endmodule

// D flip-flop
module dff(
input wire d,
input wire clk,
output reg q,
output reg q_bar
);

/*
input d, clk;
output q, q_bar;

wire d, clk;
reg q, q_bar;
*/
wire qx, qbx;

always @ (posedge clk)
begin
    q <= d;
    q_bar <= !d;
end

x x1(d, clk, qx, qbx);
x x2(d, clk, qx, qbx);
x x3(d, clk, qx, qbx);

endmodule

module dff_tb();

reg d, clk, test;
wire q, q_bar;

initial begin
    clk = 1;
end

initial begin
    $dumpfile("dff.vcd");
    $dumpvars(0, dff_tb);
    $usw_vpi();
    clk = 0;
    d = 0;
    test = 0;
    #10 d = 1;
    #10 d = 0;
    #10 d = 1;
    $display("abc...\n");
    #110;
    $finish();
end

initial begin
    #30 d = 1;
end

always begin
    #5 clk = ~clk;
end

always @ (d) begin
    test = ~d;
end

dff d1(d, clk, q, q_bar);
dff d2(d, clk, q, q_bar);
dff d3(d, clk, q, q_bar);

endmodule
