// Room: /d/huangshan/feilai.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "飛來石");
        set("long", @LONG
在平坦的山面之上，突然冒出一塊石頭，似乎除了飛來一説，別的
實在難以解釋。石面光滑，上書三字“飛來石”，遠看石頭，上粗下細，
好像搖晃不止，實在令人匪夷所思。
LONG
        );
        set("exits", ([ 
                "east"  : __DIR__"guangming",
                "north" : __DIR__"paiyun",
        ]));
        set("item_desc", ([
                "飛來石": "你可以試着推一推（push）\n",
                "stone" : "你可以試着推一推（push）\n"
        ]) );
        set("outdoors", "huangshan");
        set("coor/x", -605);
        set("coor/y", -1030);
        set("coor/z", -10);
        setup();
}
void init()
{
        add_action("do_push","push");
}
int do_push()
{
        object me = this_player();
        me->receive_damage("qi", 30);
        message_vision("$N用盡全身力氣，用力推了推飛來石，飛來石似乎晃了晃！\n",me);
        return 1;
}