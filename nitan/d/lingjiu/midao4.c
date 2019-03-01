inherit ROOM;

void create()
{
        set("short", "密道");
        set("long", @LONG
台階終于走到了頭，眼前是一間小小的石室，周圍牆壁上插著幾
盞油燈，照得石室裡一片昏黃。北邊有一條通道。
LONG );
        set("exits", ([
                "westup" : __DIR__"midao3",
                "north": __DIR__"midao5",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}