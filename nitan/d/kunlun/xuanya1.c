// Room: /d/kunlun/xuanya1.c
// Last Modified by winder on Jun. 29 2001

inherit ROOM;

void create()
{
        set("short", "懸崖");
        set("long", @LONG
你向西爬行，這邊的山勢十分兇險，直爬了半個時辰，眼前再無出
路了。你不禁臨崖浩歎，怔怔的呆了良久。
LONG        );
        set("no_clean_up", 0);
        set("exits",([
        ]));
        set("outdoors", "hongmei");
        set("coor/x", -100040);
        set("coor/y", 20010);
        set("coor/z", 40);
        setup();
}
void init()
{
        add_action("do_pa","pa");
}
int do_pa(string arg)
{
        object me;
        me=this_player();
        if (!(arg||arg=="east"||arg=="west")) return 0;
        if (arg=="east")
        {
                message("vision",me->name()+"你向東面的松樹爬去。\n",environment(me),me);
                write("你向東面的松樹年爬去。\n");
                me->move(__DIR__"songshu");
                message("vision",me->name()+"小心翼翼的爬上了松樹。\n",environment(me),me);
                return 1;
        }
        return 1;
}