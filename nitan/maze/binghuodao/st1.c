#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "密道");
        set("long", @LONG
這裡是冰火島祭壇內的一處密道，幽幽長長，深不見底不
知道通向何處。密道內燈光昏暗，陰風陣陣，不時傳來詭異的
笑聲，偶爾還觸及一兩根不知是人是獸的枯骨，讓你全身直起
雞皮疙瘩。情急之下只有四處尋路(xunlu)看看有沒新的出路。
LONG);
        set("no_sleep_room",1);
        set("objects", ([
                "/clone/dream_npc/shenlongdao/xixue-bianfu" : 6+random(8),
        ]));
        set("no_clean_up", 0);
        setup();
}

void init()
{
        object me = this_player();
        add_action("do_wang", "xunlu");
        me->start_busy(2 + random(3));

        if (random(2))
        {
                tell_object(me, HIC "你不小心踩到一副枯骨，竟然驚慌異常……\n" NOR);
        }
        else
        {
                tell_object(me, HIC "突然一群吸血蝙蝠飛過，你連忙應付 ……\n" NOR);
        }
}

int do_wang()
{
        object ob = this_player();

        message_vision(HIC "\n$N" HIC "四處亂竄，尋找新的出路，似乎發現遠處射出一絲光亮。\n"NOR, ob);

        switch (random(4))
        {
        case 0 : set("exits/east", __DIR__"st1"); break;
        case 1 : set("exits/east", __DIR__"st2"); break;
        case 2 : set("exits/east", __DIR__"st1"); break;
        default: set("exits/east", __DIR__"st2");
        }
        switch (random(4))
        {
        case 0 : set("exits/west", __DIR__"st1"); break;
        case 1 : set("exits/west", __DIR__"st1"); break;
        case 2 : set("exits/west", __DIR__"st2"); break;
        default: set("exits/west", __DIR__"st2");
        }
        switch (random(4))
        {
        case 0 : set("exits/south", __DIR__"st2"); break;
        case 1 : set("exits/south", __DIR__"st2"); break;
        case 2 : set("exits/south", __DIR__"st1"); break;
        default: set("exits/south", __DIR__"st1");
        }
        switch (random(4))
        {
        case 0 : set("exits/north", __DIR__"st2"); break;
        case 1 : set("exits/north", __DIR__"st1"); break;
        case 2 : set("exits/north", __DIR__"st2"); break;
        default: set("exits/north", __DIR__"st1");
        }
        remove_call_out("close_out");
        call_out("close_out", 15);
        return 1;
}

void close_out()
{
        if (query("exits/east"))
                delete("exits/east");

        if (query("exits/west"))
                delete("exits/west");

        if (query("exits/south"))
                delete("exits/south");

        if (query("exits/north"))
                delete("exits/north");
}
