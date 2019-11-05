contract B { function f() public {} }
contract C is B { function f() payable public {} }
// ----
// TypeError: (56-86): Overriding function is missing 'override' specifier.
// TypeError: (56-86): Trying to override non-virtual function. Did you forget to add "virtual"?
// TypeError: (56-86): Overriding function changes state mutability from "nonpayable" to "payable".
