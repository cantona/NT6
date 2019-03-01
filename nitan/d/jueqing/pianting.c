inherit ROOM;

void create()
{
        set("short", "偏廳");
        set("long", @LONG
絕情谷內堂東側便是偏廳，這裡是谷主招呼朋友談天喝茶
的地方。此處甚是清靜，偶有一兩聲鳥叫伴隨著淡淡香氣，令
人有一種說不出的舒暢。
LONG);
        set("exits", ([
               "west"   : __DIR__"neitang",
        ]));

        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}
