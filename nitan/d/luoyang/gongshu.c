// Room: /d/luoyang/gongshu.c
// Last modified by winder 2002.11.11

inherit  ROOM;

void  create  ()
{
        set("short",  "貢書處");
        set("long",  @LONG
大禹治水時，一神龜從洛河爬出，背上數字排列為“戴九履一，左
三右七，二四為肩，六八為足，五居中央”。此為洛書。大禹依照洛書
制定出治理天下之九章大法。今洛寧洛河岸邊西長水村旁，有“洛出書
處”古碑兩通，據說為當年“神龜貢書”之處。河圖洛書以天地之數奇
妙組合而涵蓋天人合一思想之宇宙圖式，反映出東方哲學思想之精髓。 
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "west" : __DIR__"dukou1",
        ]));
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("coor/x", -470);
        set("coor/y", -40);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}