inherit ROOM;

void create()
{
        set("short", "崇聖寶殿");
        set("long", @LONG
這是一座寬廣的大殿，正面有一座高約二十餘尺的佛祖寶像，通
體金光耀眼。座下香煙繚繞。大殿兩旁樹立兩根檀木大柱，題有一聯，
雲曰：　　　　　　守口攝意身莫犯　　莫惱一切諸有情　
LONG );
        set("outdoors", "tianlongsi");
        set("exits", ([
                "north" : __DIR__"ta1",
        ]));
        setup();
        replace_program(ROOM);
}