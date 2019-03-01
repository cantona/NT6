// To change a room's set
// Created by Lonely (06/19/2002)

inherit F_CLEAN_UP;
int do_one_room(object room, string arg, string i);
int main(object me, string arg)
{
        string str;
        string i;

        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;

        if (! arg || sscanf(arg, "%s %s", str, i) != 2)
                return notify_fail("指令格式：changeroom 屬性 值\n");
        do_one_room(environment(me), str, i);
        return 1;
}

int do_one_room(object room, string arg, string i)
{
        string file;
        string old;

        old=query(arg, room);

        reset_eval_cost();
        file = read_file(base_name(room)+".c");
        file = replace_string(file,"        set(\""+arg+"\", "+old+");\n","");
        file = replace_string(file,"        set(\""+arg+"\","+old+");\n","");
        file = replace_string(file,"        set(\""+arg+"\", \""+old+"\");\n","");
        file = replace_string(file,"        set(\""+arg+"\",\""+old+"\");\n","");
        file = replace_string(file,"setup",
        sprintf("set(\"%s\", %s);\n        setup",arg,i));

        if (write_file(base_name(room)+".c",file,1))
                write("Finished room "+ base_name(room) +"\n");
        return 1;
}

int  help(object  me)
{
write(@HELP
指令格式  :  changeroom 屬性 值

修改房間屬性的指令。

如果房間原本已經有該屬性，請確認set("屬性",值);之前為Tab
輸入的空格，否則先刪除原有屬性再使用本命令。

使用本命令後必須update here刷新，否則在該房間再次使用時
會造成該房間有兩個set("屬性",值)，原因不必累述。

如果值是一個字符串則要加上引號，即changeroom 屬性 "值"
例如outdoors的屬性可以這樣使用：

        changeroom outdoors "city"  

就會在房間的setup();上面加一句set("outdoors", "city");
即把房間的outdoors屬性改為city。

HELP
        );
        return  1;
}