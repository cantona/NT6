// Room: /d/suzhou/.c
// Last Modified by winder on Mar. 8 2001

inherit ROOM;

void init()
{
//        add_action("lingwu","lingwu");
        add_action("do_jump","jump");
}

void create()
{
        set("short", "樑上");
        set("long",@long
這是碧水亭上的房樑，上面畫滿了希奇古怪的字畫。
long
        );
        set("outdoors","suzhou");
        set("no_clean_up", 0);
        set("coor/x", 800);
        set("coor/y", -1200);
        set("coor/z", 10);
        setup();
}

int lingwu(string arg)
{
        object me=this_player();
        string special;
        int bl,sl;

        if (!living(me)) return 0;
        if (!arg) return notify_fail("你要領悟什麼？\n");
        if (!find_object(SKILL_D(arg)))
//         if (!find_object(SKILL_D(arg)))
                return notify_fail("沒有這種技能。\n");
        if (!me->query_skill(arg,1))
                return notify_fail("你不會這種技能。\n");
        if (!(special=me->query_skill_mapped(arg)))
                return notify_fail("你只能從特殊技能中領悟。\n");
        bl=me->query_skill(arg,1);
        if( bl>query("jing", me) || 
                query("jing", me)*100/query("max_jing", me)<20 )
        {
                me->receive_damage("jing",bl/2);
                return notify_fail("你沒辦法集中精神。\n");
        }
        sl=me->query_skill(special,1);
        if (bl > sl)
                return notify_fail("你的"+CHINESE_D->chinese(special)+"造詣不夠，無法領悟更深一層的"+CHINESE_D->chinese(arg)+"。\n");
        write("你對着字畫瞑思苦想，對"+CHINESE_D->chinese(arg)+"的體會又深了一層。\n");
        me->receive_damage("jing",bl/2);
        me->improve_skill(arg,sl/5+1);
        return 1;
}
int do_jump(string arg)
{
        object me = this_player();

        if (arg !="down") return notify_fail("你要到那去？\n");
        if( arg=="down")
        {
                write("你縱身跳下了房樑。\n");
                message("vision", me->name() + "一縱身跳下了房樑。\n", environment(me), ({me}) );
                me->move(__DIR__"bishuiting");
                message("vision", me->name() + "從上面跳了下來。\n", environment(me), ({me}) );
        }
        return 1;
}