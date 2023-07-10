
# **Welcome to the Cash Flow Minimizer**

This application
 reduces the number of transactions among a pool of people who use different modes of payment interface. There is one Treasurer (with all payment modes) to act as a Middle Man between people that have no common mode of payment .

## **Starting Over**

For example, say we have these following people.

- Satyam (Treasurer)
- Rijul
- Bhoomi
- Saket
- Anubha




#### Following are the transactions.



| *Debtor* | *Creditor*     | *Amount*                |
| :---------- :------- | :------------------------- |
| Satyam | Bhoomi | 500 |
| Rijul | Saket | 100 |
| Saket | Anubha | 435 |
| Satyam | Rijul | 520 |
| Rijul | Saket | 90 |
| Anubha | Bhoomi | 51 |
| Satyam | Saket | 679 |
| Anubha | Rijul | 234 |
| Saket | Bhoomi | 907 |
| Bhoomi | Saket| 478 |

**But here's the catch!!**
Each person only supports a limited number of payment methods and can only make or receive payments using those methods.
Only Treasurer supports all modes of payments.

#### Following are the payment modes for our example.

- Paypal
- Google_pay
- Paytm
- Razorpay
- Skrill

#### Following is list of people and payment gateways used by them.
 - Satyam   - Paypal, Google_pay, Paytm, Razorpay, Skrill
 - Rijul    - Paypal, Paytm
 - Bhoomi - Skrill,Razorpay 
 - Saket - Razorpay,Google_pay,Paytm
- Anubha - Skrill,Paypal

## **Working**

To choose the first individual, we compute the net amount for each person using the formula below and store the results in a list.


net amount = [Sum of all credits] - [Sum of all debits]

The idea is to use Greedy algorithm where at every step, settle all amounts of one person and the same process is repeated for the remaining people. 
Once net amount for every person is evaluated, find two persons with maximum and minimum net amounts and also have atleast 1 common payment gateway. These two persons X (net = x) & Y (net = y) settle payment z .Then 3 cases may arrive.

* If (magnitude of x) < y => X is completely settled and so removed from the list.
* If (magnitude of x) > y => Y is completely settled and so removed from the list.
* If (magnitude of x) = y => X and Y both are completely settled and so both are removed from the list.

The same process is repeated for the remaining people.

## **How to use?**

This system is entirely menu driven. So, when you execute the C++ application, it will instruct you and display the final result.



#### Here is the execution of our current example.




