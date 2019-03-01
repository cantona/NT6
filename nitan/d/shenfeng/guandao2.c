inherit ROOM;
void create()
{
        set("short", "塞口");
        set("long", @LONG
這裡是中原入西域的必經之路，大批的商人鴕隊都一定要
從這裡經過，形成了這裡的畸形路容。向西你可以看到一段破
舊的長城，上面好象還有被土炮轟過的痕跡，向北是一家小店。
龍門客棧的木板招牌孤零零的在寒風中搖曳。
LONG);
        set("outdoors", "gaochang");
        set("exits", ([
                  "west" : __DIR__"guandao3",
                  "north" : __DIR__"longmen",
                  "east" : __DIR__"guandao1",
        ]));
        setup();
        replace_program(ROOM);
}