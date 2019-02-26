// Room: /d/wuyi/6qu.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "六曲");
        set("long", @LONG
溪流依山而流，溪水清澈見底，水中寸許長的游魚的影子印在溪
底鵝卵石上，閃動着晶瑩的水波。兩岸樹綠竹翠，奇峯突兀。朱熹《
九曲棹歌》曰：“……六曲蒼屏饒碧灣，茆茨終日掩柴關。客來倚棹
巖花落，猿鳥不驚春意閒。……”
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "west"      : __DIR__"7qu",
                "southup"   : __DIR__"xiangshengyan",
                "southeast" : __DIR__"5qu",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1350);
        set("coor/y", -5010);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
