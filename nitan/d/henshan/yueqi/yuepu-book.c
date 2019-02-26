#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIW "「古樂譜篇」" NOR, ({ "yuepu book", "yuepu", "book" }));
        set_weight(200);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", HIW "記載着古代樂譜的筆記，你閒着沒事兒"
                            "可以看看(read)。\n" NOR);
                set("value", 50);
                set("material", "paper");
        }
        setup();
}

void init()
{
        add_action("do_read", "read");

}

int do_read(string arg)
{
        if (arg == "yuepu book" || arg == "yuepu" || arg == "book")
                return notify_fail(WHT "\n"
"---------------------------------------------------\n\n"
"                   中國古樂譜介紹\n\n"
"                       文王操\n\n"
"    漢初《韓詩外傳》記孔子向師襄學奏此曲。琴曲中講\n"
"述了周文王在渭水之濱訪子牙的故事，後世傳有《文王思\n"
"士》的曲目。存譜八至十段不等，見於《琴譜正傳》等書。\n\n"
"                       大雅\n\n"
"    因《詩經》有《大雅》而傳為周公所作。傳譜九至十\n"
"二段不等。音樂變幻重疊，有“外調莫過斯曲之妙”之謂\n"
"《琴瑟合譜》。\n\n"
"                       關雎\n\n"
"    關雎為《詩經》第一篇，孔子稱讚它“樂而不淫，哀\n"
"而不傷”。現存琴譜多為無詞曲。\n\n"
"                           鹿鳴\n\n"
"    鹿鳴為《詩經·小雅》首篇。原為周朝宴樂羣臣嘉賓\n"
"所用。為漢代僅存雅歌四篇之一。蔡邕《琴賦》以及《琴\n"
"操》均有此曲目。據説，由漢未杜夔傳至魏左延年，晉荀\n"
"勖用為行禮詩。唐韓愈：“舉於其鄉，歌‘鹿鳴’而來”\n"
"取自《送楊少尹序》。宋朱熹：此譜乃趙彥肅所傳，即是\n"
"所謂開元遺聲”。明張廷玉將此曲收人《理性元曲》，至\n"
"清朝仍有刊傳。現存曲譜與歷史記載有無聯繫，尚無定論。\n\n"
"                       湘妃怨\n\n"
"    琴歌。傳説堯的兩個女兒娥皇、女英嫁給舜。舜死後，\n"
"兩人十分悲痛，後人據此作歌，表現對親人的思念之意。\n\n"
"                        廣陵散\n\n"
"    廣陵散又名廣陵止息。現存的琴譜最早見於《神奇祕\n"
"譜》，又見於《西麓堂琴譜》，各譜均有“取韓”，“投\n"
"劍”等分段標題，因此，近人認為它源於為《琴操》所載\n"
"的《聶政刺秦王曲》。傳説晉嵇康由於不滿司馬氏專政而\n"
"遭殺害，臨刑前從容彈奏此曲，曲罷長歎：“廣陵散從此\n"
"絕矣！”後由有心人記譜而流傳至今。於是，廣陵散因嵇\n"
"康而聞名於世。明宋濂跋《太古遺音》則謂“其聲忿怒噪\n"
"急，不可為訓”。現存曲譜共四十五段。\n\n"
"                       高山流水\n\n"
"    內容根據《呂氏春秋》中伯牙在鼓琴的故事。伯牙在\n"
"琴中先表現高山，又表現流水，他的知音好友鍾子期都能\n"
"深刻領會。表明音樂可以獨立進行藝術創造，不必藉助文\n"
"詞。人們常以此為例，説明琴曲很早就可以獨奏。現存曲\n"
"譜初見於《神奇祕譜》。該書解題中説：“ 《高山流水》\n"
"本只一曲，至唐分為二曲，不分段數。宋代分《高山》四\n"
"段，《流水》八段”。《神奇祕譜》所收為不分段的，後\n"
"世流傳的多為分段 。清代川派琴家張孔山彈奏的《流水》\n"
"增強了許多滾拂手法，藉以增強水勢湍急、波濤洶湧的藝\n"
"術效果，號稱《七十二滾拂流水》或《大流水》，是近代\n"
"流傳最廣的曲目之一。近人管平湖彈奏此曲甚得好評，灌\n"
"有唱片（中國3—3122甲、乙及M-248）。另有浙江、河南\n"
"兩地同名箏曲流傳。\n\n"
"                       酒狂\n\n"
"    曲譜初見於《神奇祕譜》。魏晉竹林七賢之一阮籍由\n"
"於“歎道之不行”，“託興於酗酒”所作。樂曲素材簡煉，\n"
"描繪醉酒佯狂步履顛躓的神態。\n\n"
"---------------------------------------------------\n\n"
"\n\n" NOR);
}