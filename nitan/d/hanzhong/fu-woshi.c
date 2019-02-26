// fu-woshi.c 卧室
// Winder Oct.10 1998

inherit ROOM;
int do_pull(string arg);

void create()
{
        set("short", "卧室");
        set("long", @LONG
這裏是侯員外的卧室，卧室中央橫拉着一道大簾子。在簾後
有一張雕着八仙過海的大牀，牀頭有一個抽屜(drawer)。牀上鋪
絲陳緞，厚厚的錦被看起來很舒服，你不禁想在這裏安然大睡了。
LONG
        );
        set("sleep_room",1);
        set("exits", ([
                "north" : __DIR__"fu-houyuan",
        ]));
        set("objects", ([
                __DIR__"npc/yuanwai" : 1,
        ]));
        set("item_desc", ([
        "drawer": "一個抽屜，好像可以拉(pull)開，裏面可能有不少金銀珠寶哦。\n"
        ]) );

        set("coor/x", -12240);
	set("coor/y", 760);
	set("coor/z", 0);
	setup();
        //replace_program(ROOM);
}

void init()
{
        add_action("do_pull","pull");
}

int do_pull(string arg)
{
        object me=this_player();

        if( !arg || arg != "drawer" ) {
                return notify_fail("你要拉開什麼？\n");
        }

        message_vision("$N把抽屜拉開，還沒來得及看裏面有什麼東西，只聽得牀板吱吱
連聲，\n",this_player());
        message_vision("自動向兩邊分開，現出一個黑黝黝的洞口。\n", this_player());
        set("exits/down", __DIR__"fu-midao");
        remove_call_out("close");
        call_out("close", 5, this_object());

        return 1;
}

void close(object room)
{
        message("vision","牀板又合了起來，把洞口封住了。\n", room);
        delete("exits/down", room);
}