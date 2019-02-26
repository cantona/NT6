inherit ROOM;

void create()
{
        set("short", "石屋");
        set("long", @LONG
一間小小的石屋，屋前屋後七八株蒼松夭矯高挺，遮得石屋裏陰
沉沉的，終日不見什麼陽光。石屋內堂正中坐着一位老者，六十來歲
年紀，骨瘦如柴，臉上肌肉都凹了進去，直如一具骷髏，雙目卻炯炯
有神，正俯首撫琴。石屋四周的牆壁上掛滿了各式各樣的樂器，任何
一件都有上百或是上千光景，全是名貴之物。
LONG );
        set("exits", ([
            "out" : __DIR__"xiaoyuan",
        ]));

        set("objects", ([
                CLASS_D("meizhuang") + "/huang" : 1,
                __DIR__"obj/qin" : 1,
        ]));

        setup();
        replace_program(ROOM);
}