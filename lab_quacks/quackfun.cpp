/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 * stacks and queues portion of the lab.
 */

namespace QuackFun {

/**
 * Sums items in a stack.
 *
 * **Hint**: think recursively!
 *
 * @note You may modify the stack as long as you restore it to its original
 * values.
 *
 * @note You may use only two local variables of type T in your function.
 * Note that this function is templatized on the stack's type, so stacks of
 * objects overloading the + operator can be summed.
 *
 * @note We are using the Standard Template Library (STL) stack in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param s A stack holding values to sum.
 * @return  The sum of all the elements in the stack, leaving the original
 *          stack in the same state (unchanged).
 */
template <typename T>
T sum(stack<T>& s)
{
    if (s.size() == 0) { return T(); }
    T temp = s.top();
    s.pop();
    T added = temp + sum(s);
    s.push(temp);
    return added; // stub return value (0 for primitive types). Change this!
                // Note: T() is the default value for objects, and 0 for
                // primitive types
}

/**
 * Checks whether the given string (stored in a queue) has balanced brackets.
 * A string will consist of square bracket characters, [, ], and other
 * characters. This function will return true if and only if the square bracket
 * characters in the given string are balanced. For this to be true, all
 * brackets must be matched up correctly, with no extra, hanging, or unmatched
 * brackets. For example, the string "[hello][]" is balanced, "[[][[]a]]" is
 * balanced, "[]]" is unbalanced, "][" is unbalanced, and "))))[cs225]" is
 * balanced.
 *
 * For this function, you may only create a single local variable of type
 * `stack<char>`! No other stack or queue local objects may be declared. Note
 * that you may still declare and use other local variables of primitive types.
 *
 * @param input The queue representation of a string to check for balanced brackets in
 * @return      Whether the input string had balanced brackets
 */
bool isBalanced(queue<char> input)
{
    stack<char> s;
    while (!input.empty()) {
        if (input.front() == '[') {
            s.push(input.front());
        }
        else if (input.front() == ']') {
            if (!s.empty()) {
                s.pop();
            }
            else {
                return false;
            }
        }
        input.pop();
    }
    if (s.empty()) { return true; }
    return false;
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 *
 * **Hint**: You'll want to make a local stack variable.
 *
 * @note Any "leftover" numbers should be handled as if their block was
 * complete.
 *
 * @note We are using the Standard Template Library (STL) queue in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param q A queue of items to be scrambled
 */
template <typename T>
void scramble(queue<T>& q)
{
    stack<T> s;
    queue<T> q2;

    int iter = 1;
    while (!q.empty()) {
        if (iter%2 == 0) { // reverse on stack first
            for (int i = 0; i < iter; ++i) { // load subset onto temp stack
                if (q.empty()) { break; }
                s.push(q.front());
                q.pop();
            }
            while(!s.empty()) { // unload temp stack onto queue
                q2.push(s.top());
                s.pop();
            }
        }
        else if (iter%2 == 1) { // load straight into new queue
            for (int i = 0; i < iter; ++i) {
              if (q.empty()) { break; }
                q2.push(q.front());
                q.pop();
            }
        }
        ++iter;
    }

    while(!q2.empty()) {
        q.push(q2.front());
        q2.pop();
    }
}

/**
 * Checks if the parameter stack and queue are the same. A stack and a queue
 * are considered to the "the same" if they contain only elements of exactly
 * the same values in exactly the same order.
 *
 * @note You may assume the stack and queue contain the same number of items!
 *
 * @note The back of the queue corresponds to the top of the stack!
 *
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in
 *   your return statement, and you may only declare TWO local variables of
 *   parametrized type T to use however you wish.
 * - No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be
 *   sure to comment your code VERY well.
 *
 * @param s The stack to compare
 * @param q The queue to compare
 * @return  true if the stack and the queue are the same; false otherwise
 */
template <typename T>
bool verifySame(stack<T>& s, queue<T>& q)
{
    if (s.empty()) { return true; }

    bool retval = true;
    T temp1; // rename me
    T temp2; // rename :) -- no :)

    // copy value from stack and call recursion while stack is shortened
    temp1 = s.top();
    s.pop();
    if (!verifySame(s, q)) { retval = false; }
    s.push(temp1);

    // copy value from queue and push to back
    temp2 = q.front();
    q.pop();
    q.push(temp2);

    // compare stack and queue values
    if (temp1 != temp2) { retval = false; }

    return retval;
}

}
