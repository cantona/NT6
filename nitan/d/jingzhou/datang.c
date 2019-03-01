//Edited by fandog, 02/15/2000

inherit ROOM;
void create ()
{

        set ("short", "大堂");
        set ("long", @LONG
這裡是江陵知府的衙門大堂。兩邊是“肅靜”、“回避”的牌子，
十幾個衙役齊刷刷地站著，手拿水火棍，虎視耽耽的。知府大人坐在案
台後，冷冷地逼視著你。大堂上方掛一巨匾，上寫“明鏡高懸”四個大
字。一個師爺打扮的人站在知府大人身後，不時俯身對大人耳語幾句。
LONG);

        set("exits", ([ 
                "east" : __DIR__"huapu",
                "west" : __DIR__"yamen",
        ]));
        set("objects", ([
                "/d/city/npc/yayi" : 4,
                __DIR__"npc/shiye" : 1,
                __DIR__"npc/ling"  : 1,
        ]));

        set("no_clean_up", 0);
        set("coor/x", -1489);
        set("coor/y", -2030);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}