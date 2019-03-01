// Room: /d/mobei/yading.c
// Last Modified by winder on May. 25 2001

inherit ROOM;

void create()
{
        set ("short", "山崖頂");
        set ("long", @LONG
崖頂是個巨大的平台，積滿了皚皚白雪。幾塊巨大的石頭半臥在一
邊，形狀千奇百怪，上面有許多洞穿的小孔，風過處，如泣如訴。四邊
的山崖平平如削，幾棵矮樹就斜長于崖邊。
LONG);
        set("no_clean_up", 0);
        set("outdoors","mobei");
        set("coor/x", -250);
        set("coor/y", 5200);
        set("coor/z", 30);
        setup();
}
void init()
{
        add_action("do_jump","jump");
        add_action("do_jump","tiao");
}
int do_jump(string arg)
{
        object me = this_player();

        if (arg !="down") return notify_fail("你要跳到那去？\n");
        if( arg=="down")
        {
                write("你縱身跳下了山崖。\n");
                message("vision", me->name() + "一縱身跳下了山崖。\n", environment(me), ({me}) );
                me->move(__DIR__"downxuanya");
                message("vision", me->name() + "從山崖上面跳了下來。\n", environment(me), ({me}) );
        }
        return 1;
}