inherit ROOM;

void create()
{
        set("short", "劉府大廳");
        set("long", @LONG
劉府大廳裡異常冷清。大廳正中放著一張茶幾，上面舖了錦緞。
只見旁邊一只金光燦爛、徑長尺半的黃金盆子卻被打翻在地上。看來
這裡像是發生過打鬥。
LONG );
        set("exits", ([
                "west"   : __DIR__"liufuwest",
                "east"   : __DIR__"liufueast",
                "south"  : __DIR__"liufudayuan",
        ]));

        setup();
        replace_program(ROOM);
}