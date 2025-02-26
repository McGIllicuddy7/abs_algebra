#pragma once
    #include <string_view>
    #include <sstream>
namespace utils{
    template<typename T> std::ostream& operator<<(std::ostream& os, const std::vector<T>& obj)
    {
        os <<"[";
        for(size_t i =0; i<obj.size(); i++){
            os<< obj[i];
            if (i<obj.size()-1){
                os<<",";
            }
        }
        os <<"]";
        return os;
    }
     
    inline constexpr std::string format(const std::string_view fmt){
        return std::string(fmt);
    }
    template<typename T,typename... Args> std::string format(const std::string_view fmt,T value, Args...args){
        if(fmt.size() == 0){
            return "";
        } else{
            std::stringstream out;
            size_t index = (size_t)(-1);
            bool prev_was_open = false;
            for(size_t i =0; i<fmt.size()-1; i++){
                if (i<fmt.size()-3){
                    if (fmt[i] == '{' && fmt[i+1] == '{' && fmt[i+2] =='}' && fmt[i+3] =='}'){
                        out <<fmt.substr(0,i);
                        out << "{}";
                        std::string_view second = fmt.substr(i+4, fmt.size()-i-2); 
                        std::string tmp = format(second,args...);
                        out <<tmp;
                        return out.str();;
                    }
                }
                if(fmt[i] == '{' && fmt[i+1] == '}'&&!prev_was_open){
                    index = i;
                    break;
                } else if (fmt[i] == '{'){
                    prev_was_open = true;
                } else{
                    prev_was_open = false;
                }
            }
            std::string_view base = fmt.substr(0,index);
            std::string_view second = fmt.substr(index+2, fmt.size()-index-2);
            out << base;
            out <<value;
            std::string tmp = format(second,args...);
            out << tmp;
            return out.str();
        }
    }
    template<typename... Args>void print(const std::string_view fmt,Args...args){
        std::cout <<format(fmt, args...);
    }
    std::string right_pad(std::string s, size_t max_size){
        if(s.size()>max_size){
            throw new std::string("too long to pad");
        }
        std::string out =s;
        for(size_t i =0; i<max_size-s.size(); i++){
            out+= " ";
        }
        return out;
    }
    std::string left_pad(std::string s, size_t max_size){
        std::string out ="";
        for(size_t i =0; i<max_size-s.size(); i++){
            out+= " ";
        }
        return out+s;
    }
    std::string repeat_string(std::string s, size_t count){
        std::string out = "";
        for(size_t i =0; i<count; i++){
            out += s;
        }
        return out;
    }
}
