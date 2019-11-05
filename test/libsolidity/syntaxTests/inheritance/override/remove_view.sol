contract B { function f() public view {} }
contract C is B { function f() public {} }
// ----
// TypeError: (61-83): Overriding function is missing 'override' specifier.
// TypeError: (61-83): Trying to override non-virtual function. Did you forget to add "virtual"?
// TypeError: (61-83): Overriding function changes state mutability from "view" to "nonpayable".
