interface D {
    function f() view virtual external;
}
contract C is D {
    function f() override view external {}
}
// ----
// Warning: (18-53): Interface functions are implicitly "virtual"
