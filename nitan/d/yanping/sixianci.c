// Room: /d/yanping/sixianci.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "四賢祠");
        set("long", @LONG
延平府名優薈萃，文風昌盛。四賢祠裡供奉著楊時(yang)、羅從彥
(luo) 、李炯(li)、朱熹 (zhu)四大名儒。自楊時與遊酢 (you)“程門
立雪”之後，不負程顥“吾道南矣”之重望，由楊而羅，由羅而李，直
到集大成的朱子，代代承傳。他們上承河洛之學，在此窮首皓經，齊聲
倡儒，終于倡大閩學，著一代風流。
LONG );
        set("exits", ([
                "south" : __DIR__"ximen",
        ]));
        set("item_desc", ([
                "you" : "
    遊酢，北宋著名理學家、教育家、書法家、詩人。元豐四年(1082)，與楊
時同往穎裡，就學于程顥。五年，登進士。元佑八年(1093)，偕楊時赴洛陽求
教程頤。一日，程瞑目養神，二人不敢驚動，候立門外，待察覺時雪已盈尺，
留下“程門立雪”的千古美談。遊酢與楊時、呂大臨、謝良佐並稱程門四大弟
子。先後創辦薦山書院、豸山草堂和皖山書院等。
　　遊酢與楊時首開武夷山理學之先河。他學成南歸，于元符二年(1099)在武
夷山五曲接筍峰下築水雲寮，作為著述立說之所，撰《易學》、《詩二南義》、
《論孟雜解》、《中庸義》等。宣和五年(1123)病逝，謚“文肅”。\n",
                "yang" : "
    楊時，北宋著名理學家、教育家，號龜山，程顥最得意的弟子之一。
    他發展程顥、程頤“理”的學說，吸取張載“氣”的思想，使理學更加系
統化。
    楊時、遊酢學成南歸，程顥送別他們時說：“吾道南唉！”楊時、遊酢不
負恩師的重托，選擇了武夷山做為他們傳播理學的寶地。楊時在武夷山與寓居
武夷山麓五夫裡的胡安國及其子侄胡寧、胡寅、胡宏、胡憲，朱熹的岳父、老
師劉勉之等名賢切磋學問，交往甚密，並經常相邀遊覽武夷山。紹興五年(113
5年)逝世。清康熙年間，謚“文靖”，敕建書院、道南祠，御賜“龜山書院”
和“程氏正宗”額。傳世著作有《校正伊川易》、《三經義辨》、《列予解》、
《經筵講義》、《辨學治說》、《四書解義》、《周禮》、《毛詩辨疑》、《
楊龜山先生集》42卷、《龜山語錄》、《二程粹言》、《春秋孟子義校正》以
及《遊武夷》、《武夷紀遊》等詩。\n",
                "luo" : "
    羅從彥，北宋理學家、教育家、世稱豫章先生。崇寧二年(1103)在沙縣講
學，九年後赴洛陽求學程頤。重和元年(1118)，“築室羅源山中。絕意仕途”，
潛心著述講學，收李侗、朱鬆等為學生，常聚九峰山峽谷處講道。後在劍浦（
今延平）、連城、廣東羅浮山等地講學。建炎二年至紹興元年(1128～1131)，
受連城羅姓宗親聘請，在冠豸山仰止亭講學達四年。
    他繼承和發展程顥、程頤“窮理學說”和楊時“致和必先格物”的“理一
分殊”理論，創立“靜中觀進”說，在宋代理學發展史上起到承前啟後的作用。
卒謚“文質”。清康熙四十年(1706)御賜“奧學清節”祠額。傳世著作有《語
孟師說》、《中庸說》、《二程龜山語錄》等。\n",
                "li" : "
    李侗，宋學者、理學家、教育家，世稱延平先生。政和六年(1116)拜羅從
彥為師，繼承和發展程氏思想，主張“默坐澄心以體認天理”。李侗對朱熹的
哲學理論的發展起重大影響。從紹興二十三年(1153)到紹興三十二年，朱熹曾
四次到劍浦拜訪李侗，登門求教。李侗也曾于隆慶元年(1163)兩度到崇安五夫
裡紫陽樓看望朱熹。這年，李侗應邀赴福唐(今福清市)講學，病逝福唐，葬于
延平故裡，由朱熹卜築，並撰寫墓志銘。謚“文靖”。清康熙皇帝御書“靜中
氣象”匾額。傳世之作有《延平問答》等。 \n",
                "zhu" : "
    朱熹，南宋著名理學家、教育家、文學家。出生于尤溪。七歲到建州，十
四歲定居崇安，從學胡憲、劉勉之等。紹興十八年(1148)進士，後師事李侗，
為二程（程顥、程頤）四傳弟子。博及群書，廣注典籍，對經學、史學、文學、
樂律以及自然科學都有不同程度貢獻。
　　朱熹在哲學上發展了二程關于理氣關系的學說，集理學之大成，建立一個
完整的客觀唯心主義理學體系，認為理氣相依而不能相離，“天下未有無理之
氣，亦未有無氣之理”。把一理和萬理看作“理一分殊”的關系，強調“天理”
與“人欲”的對立，要求人們放棄“私欲”，服從“天理”。他從事教育五十
余年，強調啟發式，吸收當時科學成果，提出了對自然界變化的某些見解。他
的理學在明清兩代被提高到儒學正宗的地位。他集《大學》、《中庸》、《論
語》、《孟子》為《四子書》，成為明清兩代科舉的“聖典”，凡作經義文都
要依據朱熹的注釋和章句。卒謚“文”，清康熙二十六年(1687)，御書“學達
性天”匾額賜朱熹創辦的紫陽書院。康熙四十五年，又為朱子祠御書“大儒世
澤”匾額，並親自撰並書楹聯：“誠意正心，闡鄒魯之實學；主敬窮理，紹濂
洛之真傳。”\n",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1420);
        set("coor/y", -6180);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}