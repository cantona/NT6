//a command to generate a map for xkx ftb job system
//(admin) (arch)
// Smallfish@Huaxia

#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me,string arg)
{
        object ob;
        string filename="/clone/obj/genmap.c";
        int max_node;

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;

        if( !arg || sscanf(arg, "%d", max_node)!=1 )
                return notify_fail("map 節點數\n節點數 最好是5，到底系統能承受多少，不知道:(\n");

        if(max_node>20) 
                return notify_fail("不要亂來，小心系統崩潰!\n 最好是5，到底系統能承受多少，不知道:(\n");

        if(max_node<=0) 
                return notify_fail("負數行嗎？");

        if(!find_object(filename))      load_object(filename);
        if(!find_object(filename)) 
                return notify_fail("你的文件不全.\n");
        ob=new(filename);

        ob->start_mapping(max_node);
        return 1;
}