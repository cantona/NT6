/**********************************************************************************
*                                                                                 *
*       NameD.c 姓名生成程序                                                      *
*                                                                                 *
***********************************************************************************/

// By Zen(SnowMan.ZD) 19/09/2002
// Modified by Zen(SnowMan.ZD) 01/06/2003

// 頭文件，拼音 <-> 漢字一一對應。

#include <names.h>

protected nosave nomask int sur_size, f_size, m_size;
protected nosave nomask string *key_sur = ({ });
protected nosave nomask string *key_fname = ({ });
protected nosave nomask string *key_mname = ({ });

nomask int query_sur_size(){ return sur_size; }
nomask int query_f_size(){ return f_size; }
nomask int query_m_size(){ return m_size; }

void create() 
{ 
        seteuid( getuid() ); 
        key_sur = keys(sur_name);
        key_fname = keys(f_name);
        key_mname = keys(m_name);
        sur_size = sizeof(sur_name);
        f_size = sizeof(f_name);
        m_size = sizeof(m_name);
}

nomask string *query_s_name(string str)
{       
        if( str )
                return sur_name[str];

        return key_sur; 
}
nomask string *query_m_name(string str)
{       
        if( str )
                return m_name[str];

        return key_mname; 
}
nomask string *query_f_name(string str)
{       
        if( str )
                return f_name[str];

        return key_fname; 
}

void remove()
{
}

protected nomask string *selete_namestring(string key, int sex)
{ 
        if( sex )
                return f_name[key]; 
        return m_name[key];
} 

/*
傳回一個mapping：
        ([ name : "xxx", id : ({ "xxx", "xxx" }) ])
        name 為中文姓名，id 為拼音。
        如：
                ([ name : "高圓圓", id : ({ "gao yuanyuan", "gao", "yuanyuan" }) ])
        
可以指定的包括：
 gender = 性別, 1 = female, 0 = male.
 long_name = 名子的數目。long_name = -1， 只有一個名字，long_name = 0，隨即1-2個名字，long_name > 0，兩個名字。
 name_a = 姓
 name_b = 名
 name_c = 中間名, 如 一二三 的 二。

例子：
        random_name(0, 0, 0, 0, 0) -> 隨機男性姓名，名為隨機一個或兩個字。
        random_name(1, 0, 0, 0, 0) -> 隨機女性姓名，名為隨機一個或兩個字。
        random_name(0, 1, 0, 0, 0) -> 隨機男性姓名，名兩個字。
        random_name(0, -1, 0, 0, 0) -> 隨機男性姓名，名一個字。
        random_name(1, 1, 0, 0, 0) -> 隨機女性姓名，名兩個字。
        random_name(0, -1, 0, 0, 0) -> 隨機女性姓名，名一個字。
        
        random_name(0, 0, "李", 0, 0) -> 男姓，姓為李，名為隨機一個或兩個字。
        random_name(0, 0, 0, "強", 0) -> 男姓，姓隨機，名為隨機一個或兩個字，但最後一個字為強。
        random_name(0, 1, "李", "強", 0) -> 男姓，姓李，名為兩個字，最後一個字為強，中間隨機。
        random_name(0, 1, "李", 0, "強") -> 男姓，姓李，名為兩個字，中間一個字為強，最後隨機。
        
        random_name(0, 0, 0, 0, "強") -> 男姓，姓隨機，名隨機，但如果是兩個字，中間一個字為強。
*/
varargs nomask mapping random_name(int gender, int long_name, string name_a, string name_b, string name_c)
{       
        string str, str2, key, *names, vor, nach;
        int i;

        // write("name_a = " + name_a + ", name_b = " + name_b + ", name_c = " + name_c + "\n");
        
        // 給出了姓。
        if( name_a ){
                if( member_array(name_a, key_sur) != -1 ){
                        str = name_a;
                        vor = sur_name[str];
                }
        }
        else {
                i = random(sur_size);
                str = key_sur[i];
                vor = sur_name[str];
        }
        
        // 表格裏沒有這個字。
        if( !str || !vor )
                return 0;
        
        
        // 給出了中間名字(有long_name)，或名字(無long_name)。
        if( name_b ){
                if( gender ){
                        i = f_size;
                        while( i-- ){
                                if( member_array(name_b, f_name[key_fname[i]]) != -1 ){
                                        str2 = name_b;
                                        nach = key_fname[i];
                                        break;
                                }
                        }
                }
                else {
                        i = m_size;
                        while( i-- ){
                                if( member_array(name_b, m_name[key_mname[i]]) != -1 ){
                                        str2 = name_b;
                                        nach = key_mname[i];
                                        break;
                                }
                        }
                }
        }
        
        else {  
                if( gender ){
                        i = random(f_size);
                        key = key_fname[i];
                }
                else {
                        i = random(m_size);
                        key = key_mname[i];
                }
        
                names = selete_namestring(key, gender);
                str2 = names[random(sizeof(names))];
                nach = key;
        }
        
        // 表格裏沒有這個字。
        if( !str2 || !nach )
                return 0;
                
        // long_name = -1， 只有一個名字，long_name = 0，隨即1-2個名字，long_name > 0，兩個名字。
        if( ((!random(3) && !long_name) || long_name > 0) && long_name >= 0 ){
                if( name_c ){
                        if( gender ){
                                i = f_size;
                                while( i-- ){
                                        if( member_array(name_c, f_name[key_fname[i]]) != -1 ){
                                                str2 = name_c + str2;
                                                nach = key_fname[i] + nach;
                                                break;
                                        }
                                }
                        }
                        else {
                                i = m_size;
                                while( i-- ){
                                        if( member_array(name_c, m_name[key_mname[i]]) != -1 ){
                                                str2 = name_c + str2;
                                                nach = key_mname[i] + nach;
                                                break;
                                        }
                                }
                        }
                }
                else {
                        if( gender ){
                                i = random(f_size);
                                key = key_fname[i];
                        }
                        else {
                                i = random(m_size);
                                key = key_mname[i];
                        }
                        names = selete_namestring(key, gender);
                        str2 = names[random(sizeof(names))] + str2;
                        nach = key + nach;
                }
        }

        return ([ "name": str + str2,  "id": ({ vor + " " + nach, vor, nach }) ]); 
}

mapping man_name()
{
        return random_name(0);
}

mapping woman_name()
{
        return random_name(1);
}

// End Of File.
