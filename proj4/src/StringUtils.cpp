#include "StringUtils.h"
#include <iostream>
#include<string>
#include <cctype>
#include <cstdio>
#include <vector>
#include <string.h>
#include <cstdlib>

namespace StringUtils{

std::string Slice(const std::string &str, ssize_t start, ssize_t end) noexcept{
    std:: string CopyString = str;
    std:: string SubString;
    if (start < 0){
        start = start + CopyString.length();
    }
    if (end < 0){
        end = end + CopyString.length();
    }
    int sublength = end - start;
    if (end == 0){
        SubString = CopyString.substr(start,std::string::npos);

    }
    else{
        SubString = CopyString.substr(start,sublength);
    }
    
    return SubString;
}

std::string Capitalize(const std::string &str) noexcept{
    std::string ans = str;
    ans[0] = toupper(ans[0]);
    for (int i = 1; i < ans.length(); i++)
    {
        ans[i] = tolower(ans[i]);
    }
    return ans;
}

std::string Upper(const std::string &str) noexcept{
    std::string ans = str;
    int x = ans.length();
    for (int i = 0; i <= x; i++)
    {
        ans[i] =  toupper(ans[i]);
    }
    return ans;
}

std::string Lower(const std::string &str) noexcept{
    std::string ans = str;
    int x = ans.length();
    for (int i = 0; i <= x; i++)
    {
        ans[i] =  tolower(ans[i]);
    }
    return ans;
}

std::string LStrip(const std::string &str) noexcept{
    std::string ans;
    int start;
    for (int i = 0; i < str.length() ; i++)
    {
        if(!isspace(str[i]))
        {
            start = i;
            break;
        }
    }
    for (int i = start; i < str.length(); i++)
    {
        ans = ans + str[i]; 
    }
    return ans;
}

std::string RStrip(const std::string &str) noexcept{
    std::string ans;
    int end;
    for (int i = str.length()-1; i >= 0 ; i--)
    {
        if(!isspace(str[i]))
        {
            end = i;
            break;
        }
    }
    for (int i = end; i >= 0; i--)
    {
        ans = str[i] + ans; 
    }
    return ans;
}

std::string Strip(const std::string &str) noexcept{
    std::string ans;
    ans = StringUtils::LStrip(str);
    ans = StringUtils::RStrip(ans);
    return ans;
}

std::string Center(const std::string &str, int width, char fill) noexcept{
    std::string ans = str;
    int n = (width - str.length())/2;
    for(int i = 0; i < n; i++)
    {
        ans = fill + ans;
    }
    n = width - ans.length();
    for(int i = 0; i < n; i++)
    {
        ans = ans + fill;
    }
    return ans;
}

std::string LJust(const std::string &str, int width, char fill) noexcept{
    std::string ans = str;
    int n = width - ans.length();
    for(int i = 0; i < n; i++)
    {
        ans = ans + fill;
    }
    return ans;
}

std::string RJust(const std::string &str, int width, char fill) noexcept{
    std::string ans = str;
    int n = width - ans.length();
    for(int i = 0; i < n; i++)
    {
        ans = fill + ans;
    }
    return ans;
}

std::string Replace(const std::string &str, const std::string &old, const std::string &rep) noexcept{
    std::string ans;
    std::size_t found = str.find(old);
    int a[str.length()]={};
    a[found] = 1;
    for(int i = 1; found < str.length(); i++)
    {
        found = str.find(old,found+1);
        a[found] = 1;
    }
    
    for(int i = 0; i < str.length(); i++)
    {
        if(a[i] == 1)
        {
            ans = ans + rep;
            i = i + old.length()-1;
        }
        else
        {
            ans = ans + str[i];
        }

    }

    return ans;
}


std::vector< std::string > Split(const std::string &str, const std::string &splt) noexcept{
    std::string spl = splt;
    std::vector<std::string>vtr;
    int size = spl.length();;
    std::string ans;
    if (splt == "") 
    {
        for(int i = 0; i < str.length(); i++)
        {
            if(isspace(str[i]))
            {
                if(!isspace(str[i+1]))
                {
                    vtr.push_back(ans);
                    ans = "";
                }     
            }
            else
            {
                ans = ans + str[i];
            }
        }
        vtr.push_back(ans);
    }
    
   else
   {
       std::size_t found = str.find(spl);
        int a[str.length()]={};
        a[found] = 1;
        for(int i = 1; found < str.length(); i++)
        {
            found = str.find(spl,found+1);
            a[found] = 1;
        }
        
        for(int i = 0; i < str.length(); i++)
        {
            if(a[i] == 1)
            {
                vtr.push_back(ans);
                ans = "";
                i = i + size-1;
            }
            else
            {
                ans = ans + str[i];
            }
        }
        if(ans != "")
        {
            vtr.push_back(ans);
        }

   }
    return vtr;
    
}  

std::string Join(const std::string &str, const std::vector< std::string > &vect) noexcept{
    std::string ans = vect[0];
    for(int i = 1; i < vect.size(); i++)
    {
        ans = ans + str + vect[i];
    }
    return ans;
}

std::string ExpandTabs(const std::string &str, int tabsize) noexcept{
    std::vector <std::string> vtr = StringUtils::Split(str,"\t");
    std::string seg;
    std::string ans;
    int length;
    if (tabsize == 0)
    {
        ans = StringUtils::Replace(str,"\t","");
    }
    else
    {
        for (int i = 0; i < vtr.size()-1; i++)
        {
            if(vtr[i].length() < tabsize)
            {
                length = tabsize - vtr[i].length();
            }
            else if (vtr[i].length() % tabsize == 0)
            {
                length = tabsize;
            }
            else
            {
                length = tabsize - (vtr[i].length() % tabsize);
            }
            seg = vtr[i];
            for (int j = 0; j <length; j++)
            {
                seg = seg + " ";
            }
            ans = ans + seg;
        }
        ans = ans + vtr[vtr.size()-1];
    }
    return ans;
}

int EditDistance(const std::string &left, const std::string &right, bool ignorecase) noexcept{
    int m = left.length();
    int n = right.length();
    int v0[n+1];//create first row
    int v1[n+1];//create second row
    int deletecost;
    int insertcost;
    int substitutioncost;
    
    for (int i = 0; i <= n; i++)//assign every element in first row to its index
    {
        v0[i] = i;
    }

    for(int i = 0; i < m; i++)
    {
        v1[0] = i+1;
        for (int j = 0; j <= n; j++)
        {
            if(!ignorecase)
            {
                if(left[i] == right[j])
                {
                    
                    v1[j+1] = v0[j];
                }
                else
                {
                    v1[j+1] = std::min(v0[j],std::min(v1[j],v0[j+1]))+1;
                }
            }
            else
            {
                if(tolower(left[i]) == tolower(right[j]))
                {
                    v1[j+1] = v0[j];
                }
                else
                {
                    v1[j+1] = std::min(v0[j],std::min(v1[j],v0[j+1]))+1;
                }
            }

        }
        for(int i = 0; i <= n; i ++)
        {
            v0[i] = v1[i];
        }
    }
    return v0[n];
}
//learn the alg from https://en.wikipedia.org/wiki/Levenshtein_distance#:~:text=In%20information%20theory%2C%20linguistics%2C%20and%20computer%20science%2C%20the,required%20to%20change%20one%20word%20into%20the%20other.

    
};

