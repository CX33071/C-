class MyQueue{
    public:
     static<int> StaticIn;
     static<int> StaticOut;
     MyQueue() {

     };
     void push(int x) { StaticIn.push(x);
     }
     int pop(){
        if(StaticOut.empty()){
            while(!StaticIn.empty()){
                Static.Out.push(StaticIn.top());
                StaticIn.pop();
            }
        }
        int result = StaticOut.top();
        StaticOut.pop();
        return result;
     }
     int peek() { 
        int result = StaticOut.top();
         StaticOut.push(result);
         return result;
     }
     bool empty() { 
        return StaticIn.empty() & StaticOut.empty(); }
}