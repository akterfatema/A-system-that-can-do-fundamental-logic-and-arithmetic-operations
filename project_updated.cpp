// #include <iostream>
#include <bits/stdc++.h>
using namespace std;
#define maxx 100000000
double operation(double a, double b, char op)
{
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    default:
        return pow(a, b);
    }
}

int precedence(char c)
{
    if (c == '^')
        return 3;
    else if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

double simplify(string term)
{
    stack<double> operand;
    stack<double> opertor;
    for (int i = 0; i < term.length(); i++)
    {
        
        if (isdigit(term[i]))
        {
            // determining whether the number is double or contains multiple digits
            string temp = "";
            while (i < term.length() and (isdigit(term[i]) || term[i] == '.'))
            {
                temp += term[i];
                i++;
            }
            operand.push(std::stod(temp));
            i--;
        }
        else if (term[i] == ')')
        {
            while (!opertor.empty() and opertor.top() != '(')
            {
                double oprnd1 = operand.top();
                operand.pop();

                double oprnd2 = operand.top();
                operand.pop();

                char op = opertor.top();
                opertor.pop();
                // cout << "T: " << oprnd1 << " " << oprnd2 << " " << op << endl;
                operand.push(operation(oprnd2, oprnd1, op));
            }
            if (opertor.top() == '(')
            {
                opertor.pop();
            }
        }
        else if (term[i] == '(')
        {
            opertor.push(term[i]);
        }
        else
        {
            // term[i] is a operator +-*/^
            while (!opertor.empty() && precedence(opertor.top()) >= precedence(term[i]))
            {
                double operand1 = operand.top();
                operand.pop();

                double operand2 = operand.top();
                operand.pop();

                char op = opertor.top();
                opertor.pop();

                operand.push(operation(operand2, operand1, op));
            }

            opertor.push(term[i]);
        }
    }
    while (!opertor.empty())
    {
        double oprnd1 = operand.top();
        operand.pop();

        double oprnd2 = operand.top();
        operand.pop();

        char op = opertor.top();
        opertor.pop();
        // cout << "T: " << oprnd1 << " " << oprnd2 << " " << op << endl;
        operand.push(operation(oprnd2, oprnd1, op));
    }
    return operand.top();
}

string InToPost()
{
    string s;
    cout << "Enter Infix term: ";
    cin >> s;
    stack<char> st;
    string res;

    for (int i = 0; i < s.length(); i++)
    {
        if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
        {
            res += s[i];
        }
        else if (s[i] == '(')
        {
            st.push(s[i]);
        }
        else if (s[i] == ')')
        {
            while (!st.empty() && st.top() != '(')
            {
                res += st.top();
                st.pop();
            }
            if (st.top() == '(')
            {
                st.pop(); // Popping '(' here
            }
        }
        else
        {
            while (!st.empty() && precedence(st.top()) >= precedence(s[i]))
            {
                res += st.top();
                st.pop();
            }
            st.push(s[i]);
        }
    }

    while (!st.empty())
    {
        res += st.top();
        st.pop();
    }

    return res;
}

string PostToIn()
{
    string term;
    cout << "Enter Postfix term: ";
    cin >> term;

    stack<string> stack;

    for (int i = 0; i < term.length(); i++)
    {
        if ((term[i] >= 'a' && term[i] <= 'z') || (term[i] >= 'A' && term[i] <= 'Z'))
        {
            // the following line is assigning term[i]'th element into the variable op
            // term[i] = 'a'
            // op(1, term[i]) = 'a'
            // op(2, term[i]) = 'aa'
            string op(1, term[i]);
            stack.push(op);
        }
        else
        {
            string op1 = stack.top();
            stack.pop();
            string op2 = stack.top();
            stack.pop();
            if (stack.size() == 0)
            {
                stack.push(op2 + term[i] +
                           op1);
            }
            else
            {
                stack.push("(" + op2 + term[i] +
                           op1 + ")");
            }
        }
    }

    return stack.top();
}

void swap(double *a, double *b)
{
    double t = *a;
    *a = *b;
    *b = t;
}

int ascend_partition(double arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        // 5 4 1 2 3
        // 1 4 5 2 3
        // 1 2 5 4 3

        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
        // 1 2 3 4 5
    swap(&arr[i + 1], &arr[high]);
    return (i + 1); //3
}

int descend_partition(double arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {

        if (arr[j] > pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void ascend_quickSort(double arr[], int low, int high)
{
    if (low < high)
    {

        int pi = ascend_partition(arr, low, high);

        ascend_quickSort(arr, low, pi - 1);
        ascend_quickSort(arr, pi + 1, high);
    }
}

void descend_quickSort(double arr[], int low, int high)
{
    if (low < high)
    {

        int pi = descend_partition(arr, low, high);

        descend_quickSort(arr, low, pi - 1);
        descend_quickSort(arr, pi + 1, high);
    }
}

string strBitwiseAND(string arr[], int n)
{
    string res = "";

    int largest_size = INT_MIN;

    for (int i = 0; i < n; i++)
    {
        largest_size = max(largest_size, (int)arr[i].length());
    }

    for(int i = 0; i< n; i++)
    {
        while (arr[i].length() != largest_size)
        {
            arr[i] = "0"+arr[i];
        }
        // cout << arr[i] << endl;
    }
    for (int i = 0; i < largest_size; i++)
    {
        int flag = 1;
        for (int j = 0; j < n; j++)
        {
            if(arr[j][i] == '0'){
                res += "0";
                flag = 0;
                break;
            }
        }
        if(flag == 1)
        {
            res += "1";
        }
        
    }
    
    return res;

}

string strBitwiseOR(string *arr, int n)
{
    string res = "";

    int largest_size = INT_MIN;

    for (int i = 0; i < n; i++)
    {
        largest_size = max(largest_size, (int)arr[i].length());
    }

    for (int i = 0; i < n; i++)
    {
        while (arr[i].length() != largest_size)
        {
            arr[i] = "0" + arr[i];
        }
        // cout << arr[i] << endl;
    }
    for (int i = 0; i < largest_size; i++)
    {
        int flag = 1;
        for (int j = 0; j < n; j++)
        {
            if (arr[j][i] == '1')
            {
                res += "1";
                flag = 0;
                break;
            }
        }
        if (flag == 1)
        {
            res += "0";
        }
    }

    return res;
}

string strBitwiseXor(string *arr, int n)
{
    string res = "";

    int largest_size = INT_MIN;

    for (int i = 0; i < n; i++)
    {
        largest_size = max(largest_size, (int)arr[i].length());
    }

    for (int i = 0; i < n; i++)
    {
        while (arr[i].length() != largest_size)
        {
            arr[i] = "0" + arr[i];
        }
        // cout << arr[i] << endl;
    }
    for (int i = 0; i < largest_size; i++)
    {
        int flag = 1;
        for (int j = 0; j < n; j++)
        {
            if (arr[j][i] != arr[0][i])
            {
                res += "1";
                flag = 0;
                break;
            }
        }
        if (flag == 1)
        {
            res += "0";
        }
    }

    return res;
}

string strNot(string term)
{
    string result = term;
    for (int i = 0; i < term.length(); i++)
    {
        if (term[i] == '0')
        {
            result[i] = '1';
        }
        else
        {
            result[i] = '0';
        }
    }
    return result;
}

void logic_operations()
{
    while (true)
    {
        cout << "\nChose Operation: " << endl;
        cout << "1. AND" << endl;
        cout << "2. OR" << endl;
        cout << "3. NOT" << endl;
        cout << "4. NAND" << endl;
        cout << "5. NOR" << endl;
        cout << "6. XOR" << endl;
        cout << "7. XNOR" << endl;
        cout << "8. Back to Main Menu" << endl;
        cout << "Choice: ";
        int choice;
        cin >> choice;
        //        string inp1, inp2;

        // if (choice == 3){
        //     cin >> inp1;
        // }else{
        //     cin >> inp1 >> inp2;
        // }

        if (choice == 1)
        {
            int n;
            cout << "How Many Number of Strings? ";
            cin >> n;
            string arr[n];
            cout << "Enter the bit strings: ";
            for (int i = 0; i < n; i++)
            {
                cin >> arr[i];
            }
            cout << "\tResult: " << strBitwiseAND(arr, n) << endl;
        }
        else if (choice == 2)
        {
            int n;
            cout << "How Many Number of Strings? ";
            cin >> n;
            string arr[n];
            cout << "Enter the bit strings: ";
            for (int i = 0; i < n; i++)
            {
                cin >> arr[i];
            }
            cout << "\tResult: " << strBitwiseOR(arr, n) << endl;
        }
        else if (choice == 3)
        {
            string inp;
            cout << "Enter a string: ";
            cin >> inp;
            cout << "\tResult: " << strNot(inp) << endl;
        }
        else if (choice == 4)
        {
            int n;
            cout << "How Many Number of Strings? ";
            cin >> n;
            string arr[n];
            cout << "Enter the bit strings: ";
            for (int i = 0; i < n; i++)
            {
                cin >> arr[i];
            }
            cout << "\tResult: " << strNot(strBitwiseAND(arr, n)) << endl;
        }
        else if (choice == 5)
        {
            int n;
            cout << "How Many Number of Strings? ";
            cin >> n;
            string arr[n];
            cout << "Enter the bit strings: ";
            for (int i = 0; i < n; i++)
            {
                cin >> arr[i];
            }
            cout << "\tResult: " << strNot(strBitwiseOR(arr, n)) << endl;
        }
        else if (choice == 6)
        {
            int n;
            cout << "How Many Number of Strings? ";
            cin >> n;
            string arr[n];
            cout << "Enter the bit strings: ";
            for (int i = 0; i < n; i++)
            {
                cin >> arr[i];
            }
            cout << "\tResult: " << strBitwiseXor(arr, n) << endl;
        }
        else if (choice == 7)
        {
            int n;
            cout << "How Many Number of Strings? ";
            cin >> n;
            string arr[n];
            cout << "Enter the bit strings: ";
            for (int i = 0; i < n; i++)
            {
                cin >> arr[i];
            }
            cout << "\tResult: " << strNot(strBitwiseXor(arr, n)) << endl;
        }
        else if (choice == 8)
        {
            return;
        }
    }
}

void other_features()
{
    while (true)
    {
        cout << "\n\n1. Mod operation" << endl;
        cout << "2. Percentage Operation" << endl;
        cout << "3. Logarithms" << endl;
        cout << "4. Trigonometry" << endl;
        cout << "5. Square Root" << endl;
        cout << "6. Back to Main Menu" << endl;
        cout << "Choice: ";
        int choice;
        cin >> choice;
        if (choice == 1)
        {
            cout << "Enter two values X and Y (X mod Y): ";
            int inp1, inp2;
            cin >> inp1 >> inp2;
            cout << "\tResult: " << inp1 % inp2 << endl;
        }
        else if(choice==6){
            return;
        }
        else if (choice == 3)
        {
            cout << "\n1. e-base log or Ln()" << endl;
            cout << "2. 10-base log()" << endl;
            cout << "Choose: ";
            int choice2;
            cin >> choice2;
            if (choice2 == 1)
            {
                cout << "Enter a value: ";
                double val;
                cin>>val;
                cout << "\tResult: " << log(val) << endl;
            }
            else if (choice2 == 2)
            {
                cout << "Enter a value: ";
                double val;
                cin>>val;
                cout << "\tResult: " << log10(val) << endl;
            }
        }
        else if (choice == 5)
        {
            cout << "Enter the value: ";
            double inp1;
            cin >> inp1;
            cout << "\tResult: " << sqrt(inp1) << endl;
        }
        else if (choice == 2)
        {

            cout << "Enter two values X and Y (X % Y): ";
            double inp1, inp2;
            cin >> inp1 >> inp2;
            cout << "\tResult: " << inp1 * (inp2/100) << endl;
        }
        else if (choice == 4)
        {

            cout << "\n\n1. Sin" << endl;
            cout << "2. Cos" << endl;
            cout << "3. Tan" << endl;
            cout << "4. Cot" << endl;
            cout << "5. Sec" << endl;
            cout << "6. Cosec" << endl;
            cout << "Choice: ";
            int ch;
            cin >> ch;
            if(ch==1){
             cout<<"Enter the value in radian: ";
             double value;
             cin>>value;
             cout<<"\tResult: "<<sin(value)<<endl;
            }
             else if(ch==2){
             cout<<"Enter the value in radian: ";
             double value;
             cin>>value;
             cout<<"\tResult: "<<cos(value)<<endl;
            }
            else if(ch==3){
             cout<<"Enter the value in radian: ";
             double value;
             cin>>value;
             cout<<"\tResult: "<<tan(value)<<endl;
            }
            else if(ch==4){
             cout<<"Enter the value in radian: ";
             double value;
             cin>>value;
             cout<<"\tResult: "<<1/tan(value)<<endl;
            }
            else if(ch==5){
             cout<<"Enter the value in radian: ";
             double value;
             cin>>value;
             cout<<"\tResult: "<<1/cos(value)<<endl;
            }
            else if(ch==6){
             cout<<"Enter the value in radian: ";
             double value;
             cin>>value;
             cout<<"\tResult: "<<1/sin(value)<<endl;
            }
        }
    }
}

int main()
{
    while (true)
    {
        cout << "\nChoose desired operation from below:" << endl;
        cout << "1. Logic operations" << endl;
        cout << "2. Arithmetic Operations" << endl;
        cout << "3. Infix to Postfix" << endl;
        cout << "4. Postfix to infix" << endl;
        cout << "5. Ascending Sort" << endl;
        cout << "6. Descending Sort" << endl;
        cout << "7. Other features" << endl;
        cout << "Choice: ";
        int option;
        // getline(cin, op);
        cin >> option;
        // cout << op << endl;
        if (option == 1)
        {
            logic_operations();
        }
        else if (option == 3)
        {
            string res = InToPost();
            cout << "Postfix: " << res << endl;
        }
        else if (option == 4)
        {
            string res = PostToIn();
            cout << "Infix: " << res << endl;
        }
        else if (option == 5)
        {
            int n;
            cout << "Enter the size of array: ";
            cin >> n;
            cout << "Enter the array: ";
            double arr[n + 5];
            for (int i = 0; i < n; i++)
            {
                cin >> arr[i];
            }
            ascend_quickSort(arr, 0, n - 1);
            cout << "Sorted array: ";
            for (int i = 0; i < n; i++)
            {
                cout << arr[i] << " ";
            }
            cout << endl;
        }
        else if (option == 6) // descending sort
        {
            int n;
            cout << "Enter the size of array: ";
            cin >> n;
            cout << "Enter the array: ";
            double arr[n + 5];
            for (int i = 0; i < n; i++)
            {
                cin >> arr[i];
            }
            descend_quickSort(arr, 0, n - 1);
            cout << "Sorted array: ";
            for (int i = 0; i < n; i++)
            {
                cout << arr[i] << " ";
            }
            cout << endl;
        }
        else if (option == 7)
        {
            other_features();
        }
        else if (option == 2)
        {
            string inp;
            cout << "Enter the term: ";
            // getline(cin, inp);
            cin >> inp;
            double res = simplify(inp);
            cout << "\tResult = " << res << endl;
        }
    }
}
