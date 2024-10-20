class Solution {
public:
    bool parseBoolExpr(std::string& expression) {
        for(char& ch: expression) {
            if(ch == ',') ch = '.';
            if(ch == 't') ch = '1'; if(ch == 'f') ch = '0';
        }

        std::stack<char> opr, exp;        
        for(char& ch: expression) {
            if(ch == '.') continue;
            if(ch == '!' or ch == '&' or ch == '|') { opr.push(ch); continue; }
            if(ch == '(' or ch == '0' or ch == '1') { exp.push(ch); continue; }

            char x = exp.top(); exp.pop();
            int ix = x - '0';
                    
            if(opr.top() == '!') { ix = !ix; }
            else {
                while(exp.top() != '(') {
                    char y = exp.top(); exp.pop();
                    int iy = y - '0';

                    if(opr.top() == '&') ix &= iy;
                    if(opr.top() == '|') ix |= iy;
                }
            }
            opr.pop(); 
            exp.pop();
            exp.push(ix + '0');
        }

        return (exp.top() == '1')? true: false;
    }
};
