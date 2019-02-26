// This is a room made by wsl.
inherit ROOM;
void create()
{
    set("short", "秦皇陵");
        set("long", @LONG
走出墓穴，眼前豁然開朗，在這浩大的地下宮殿裏，卻一點都不
覺得和地面有什麼區別，頂上鑲嵌着無數散發着熒光的『星星』，足
以讓你看清四周的景象了。
LONG );
    set("exits", ([
       "east" :__DIR__"shendao",
]));
    setup();
    replace_program(ROOM);
}