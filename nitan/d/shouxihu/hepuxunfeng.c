// Room: /yangzhou/hepuxunfeng.c
// Last Modified by Winder on Jul. 20 2000

inherit ROOM;

void create()
{
        set("short","荷浦熏風");
        set("long",@LONG
荷浦熏風位于長堤春柳東岸。為清乾隆布政使銜江春所築家園，故
稱“江園”。乾隆高宗南巡時賜名凈香園。園內有清華堂、青雨廊、杏
花春雨之堂，又有怡性堂、翠玲瓏館及涵虛閣。涵虛閣外，構小亭置四
屏風，嵌“荷浦熏風”四字。此處前湖後浦，分種紅、白荷花。夏日臨
湖小憩，熏風拂面，令人呼吸清涼，熱念頓消。
    江園內飛甍反宇，五色填漆，一片金碧，照耀湖山，每當夕陽西下，
殿角鈴聲與畫船簫鼓輒相應答。
LONG );
        set("outdoors", "shouxihu");

        set("exits", ([
                "north" : __DIR__"siqiaoyanyu",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 2);
        set("coor/y", 39);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}