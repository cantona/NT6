inherit ROOM;

void create()
{
        set("short", "草原");
        set("long", @LONG
這裡是一望無際的大草原。綠色的草地美麗得就象晴朗的
藍天。草原上三三兩兩的羊群則是藍天上飄浮的朵朵白雲。遠
處的昆侖山在驕陽下看來亮如純銀；到了夕陽西下時又變得燦
爛如黃金。你也許從沒想到，在塞外的邊陲之地竟有如此美妙
的地方，美得輝煌而神秘，美得令人迷惑。
LONG);
        set("outdoors", "gaochang");
        set("exits", ([
                  "westup" : __DIR__"caoyuan7",
                  "east" : __DIR__"xingxing2",
        ]));
        setup();
        replace_program(ROOM);
}