// fu-woshi.c 臥室
// Winder Oct.10 1998

inherit ROOM;
int do_pull(string arg);

void create()
{
        set("short", "臥室");
        set("long", @LONG
這裡是侯員外的臥室，臥室中央橫拉著一道大簾子。在簾後
有一張雕著八仙過海的大床，床頭有一個抽屜(drawer)。床上舖
絲陳緞，厚厚的錦被看起來很舒服，你不禁想在這裡安然大睡了。
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
        "drawer": "一個抽屜，好象可以拉(pull)開，裡面可能有不少金銀珠寶哦。\n"
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

        message_vision("$N把抽屜拉開，還沒來得及看裡面有什麼東西，只聽得床板吱吱
連聲，\n",this_player());
        message_vision("自動向兩邊分開，現出一個黑黝黝的洞口。\n", this_player());
        set("exits/down", __DIR__"fu-midao");
        remove_call_out("close");
        call_out("close", 5, this_object());

        return 1;
}

void close(object room)
{
        message("vision","床板又合了起來，把洞口封住了。\n", room);
        delete("exits/down", room);
}