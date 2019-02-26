#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "大雄寶殿");
        set("long", @LONG
這是峨嵋山華藏庵的大雄寶殿。正中供奉着普賢菩薩。有羣青衣
小師太正在地上誦經。後面有道小門通往後殿。後殿是峨嵋派第三代
掌門人滅絕師太傳功的地方。
LONG );
        set("exits", ([
                "north" : __DIR__"hcaguangchang", 
                "south" : __DIR__"hcahoudian", 
        ]));
        set("objects", ([
                __DIR__"obj/xiang" : 1,
        ]));
        set("no_clean_up", 0);
        setup();
}

void init()
{
        add_action("do_move", "move");
}

int do_move(string arg)
{
        object me = this_player();

        if (! arg || arg != "xiang")
                return notify_fail("你要移動什麼？\n");

        if (query("exits/down"))
                return notify_fail("座像已經被移開了。\n");

        message_vision(HIC "\n$N" HIC "剛一推動" NOR + YEL "普賢菩薩像"
                       HIC "，那座像卻自己向一方移開，地面現出一個洞口"
                       "。\n\n" NOR, me);
        set("exits/down", __DIR__"midao");
        remove_call_out("close");
        call_out("close", 8, this_object());

        return 1;
}

void close(object room)
{
        message("vision", WHT "忽然只聽「喀喀喀」幾聲，" YEL "普賢菩薩像"
                          WHT "縮回原地，把密道擋住了。\n" NOR, room);
        delete("exits/down", room);
}