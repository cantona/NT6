inherit ROOM;
#include <ansi.h>

void create()
{
    set("short", "大廳");
    set("long", 
"這裡是桃花山莊的正廳。整個大廳十分寬闊。廳中更掛滿\n"
"了各種名家的書法真跡。但最為顯眼的卻是正中掛的一幅對聯：\n\n"
HIC "           ※※※※※※※※※※※※※※※\n"
"           ※                          ※\n"
"           ※   " HIW "桃 花 影 落 飛 神 劍" HIC  "   ※\n"
"           ※                          ※\n"
"           ※   " HIW "碧 海 潮 生 按 玉 簫" HIC  "   ※\n"
"           ※                          ※\n"
"           ※※※※※※※※※※※※※※※\n\n" NOR
"其字體遒勁挺拔，氣勢宏偉之極，想必應是出自黃藥師的手筆。\n"
);
        set("exits", ([
            "north" : __DIR__"qianyuan",
            "south" : __DIR__"houyuan",
            "east"  : __DIR__"daojufang",
            "west"  : __DIR__"wofang" ,
        ]));
        set("objects", ([
            //"/kungfu/class/taohua/huang" : 1, // 已經取消該區域
        ]) );    
        set("valid_startroom", 1);
        set("no_beg", "1");
        setup();

}

int valid_leave(object me, string dir)
{
        object guarder;

        if (! objectp(guarder = present("huang yaoshi", this_object())))
                return 1;

        if (dir == "south" || dir == "east")
                return guarder->permit_pass(me, dir);

        return 1;
}
