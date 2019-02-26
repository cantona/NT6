#include <ansi.h>
#define TOTALRATE       1000
inherit COMBINED_ITEM;

int open_baoxiang(object me,object this);
string test(object me,object this);

string extra_long() 
{
        string str;
        mixed key,list;
        object ob;
        int i;
        str = this_object()->name()+"中可能開出的獎勵包括：\n";
        list = query("BAOXIANG_LIST", this_object());
        if(!list || !mapp(list) ) {
                return str;
        }
        key = keys(list);
        for(i=0;i<sizeof(key);i++) {
                ob = load_object(key[i]);
                if(ob) {
                        str += "\t"+ob->name()+"("+query("id",ob)+")\n";
                }
        }
        return str;


}

int do_test(string arg)
{
        object me,this;
        me = this_player();

        this = this_object();

        if( !arg ) return notify_fail("你要測試什麼？\n"); 
        if(present(arg,environment()) != this) {
                return 0;
        }

        tell_object(me,test(me,this)+"\n");
        return 1;
}

string test(object me,object this)
{
        mixed list;
        string str;
        mixed keys;
        object ob;
        int totalRate;
        int i;

        str = this->name()+"\n";

        list = query("BAOXIANG_LIST", this);

        if(!list || !mapp(list)) {
                str += "上沒有BAOXIANG_LIST屬性，或者該屬性不是mapping！";
        } else {
                keys = keys(list);
                if(!sizeof(keys)) {
                        str += "BAOXIANG_LIST列表為空！";
                } else {
                        totalRate = 0;
                        for(i=0;i<sizeof(keys);i++) {
                                totalRate += list[keys[i]];
                                ob = load_object(keys[i]);      
                                if(!ob) {
                                        str += keys[i]+"（概率："+list[keys[i]]+"）加載失敗，可能無文件或文件編譯錯誤\n";
                                } else {
                                        str += keys[i]+"["+ob->name()+"]"+"（概率："+list[keys[i]]+"）正常。\n";
                                }
                        }

                        if(totalRate == TOTALRATE) {
                                str += "總概率："+totalRate+"正常。";
                        } else {
                                str += "總概率："+totalRate+"不正常！！！！";
                        }
                }

        }
        return str;

}

int do_open(string arg)
{
        object me,this;
        me = this_player();
        this = this_object();
        if( !arg ) return notify_fail("你要打開什麼？\n");
        if(present(arg,environment()) != this) {
                return 0;
        }
        if(this->query_amount()) {
                if(open_baoxiang(me,this)) {
                        this->add_amount(-1);
                        return 1;
                } else {
                        return 0;
                }
        } else {
                return 0;
        }
}

int open_baoxiang(object me,object this)
{
        mixed list;
        object ob;
        mixed keys;
        int totalRate;
        int rand;       
        int i;

        string str;

        list = query("BAOXIANG_LIST", this);
        
        if(!list || !mapp(list)) {
                return 0;
        }
        
        totalRate = 0;
        rand = random(TOTALRATE);       

        keys = keys(list);
        for(i=0;i<sizeof(list);i++) {
                if(rand >= totalRate && rand < totalRate+list[keys[i]]) {
                        ob = new(keys[i]);
                        if(ob && ob->move(me)) {
                                str = "打開了一個"+this->name()+"，從裏邊得到了"+ob->name()+"("+query("id",ob)+")。\n";
                                tell_room(environment(me),me->name()+str,({me}));
                                tell_object(me,"你"+str);
                                return 1;
                        } else {
                                if(ob) {
                                        tell_object(me,"打開"+this->name()+"失敗了。\n");
                                        destruct(ob);
                                }
                                return 0;
                        }
                } else {
                        totalRate += list[keys[i]];
                }
        }
        return 0;
}

