#include <ansi.h>; 
inherit ROOM;

void create()
{
          set("short", "百丈澗");
        set("long", @LONG
山道到此突然消失，在你面前是一條山澗，山澗之中雲霧繚繞，
你根本無法看清對面。一條鐵索(tiesuo)深入雲中，旁邊有一塊石碑。
LONG );
          set("outdoors", "lingjiu");
          set("exits",([
                      "southdown" : __DIR__"yan",
          ]));
          set("objects",([
                CLASS_D("lingjiu") + "/yupopo" : 1,
          ]));
          set("item_desc",([
                      "tiesuo" : YEL "這條鐵索是通往對面的接天橋，你"
                           "也許可以走(zou)過去。\n" NOR,
          ]));
          setup();
}

void init()
{
        add_action("do_zou", "zou");
}

int do_zou(string arg)
{
        object me = this_player(), room;

        if (! arg || arg != "tiesuo")
                return notify_fail("你要走什麼？\n");

        if (! (room = find_object(__DIR__"xianchou")))
                room = load_object(__DIR__"xianchou");

        if (! objectp(room))
                return notify_fail(HIW "你大叫道：BUG！BUG！\n" NOR);

        message_vision(HIW "\n只見$N" HIW "輕輕躍上鐵索，飄然而"
                       "去。\n" NOR, me);
        me->move(room);
        message_vision(HIW "$N" HIW "從鐵索上飄然而下，來到這縹"
                       "緲峯絕頂。\n" NOR, me);
        return 1;
}