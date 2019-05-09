#include <iostream>
#include <array>

using LargeNumber = std::array<char, 52>;
using NumberArray = std::array<const char* const, 100>;

static constexpr LargeNumber sum(const NumberArray& numbers) noexcept
{
    LargeNumber total{};
    for (char& c : total)
        c = '0';
    
    int numDigitsInTotal = 50;
    for (const char* const number : numbers)
    {
        int carry = 0;
        for (int i = 0; i < 50; ++i)
        {
            const int digit1 = total[i] - '0';
            const int digit2 = number[i] - '0';
            const int sum = digit1 + digit2 + carry;

            carry = sum / 10;
            total[i] = (sum % 10) + '0';
        }

        if (carry != 0)
        {
            for (int i = 50; i < numDigitsInTotal; ++i)
            {
                const int digit = total[i] - '0';
                const int sum = digit + carry;

                carry = sum / 10;
                total[i] = (sum % 10) + '0';
            }
        }

        if (carry != 0)
        {
            total[numDigitsInTotal] = carry + '0';
            ++numDigitsInTotal;
        }
    }

    return total;
}

int main()
{
    // Numbers stored back-to-front to make loop logic easier
    static constexpr NumberArray numbers = {
        "05204753101564209573802289979789720120933578270173",
        "83506281071405087007969842184621790009477673967364",
        "92690371662732185031590333247495014742599168942347",
        "05280945160427011810336503422527516147536331224919",
        "67664236087731574012401308917117164393570288576032",
        "75762716343787148638381487363102833632669607616298",
        "83723898857219612629513918456080497994821897821182",
        "81398127207678469767822498532912302523471982247244",
        "67235130611788544865861276119093460310063754415474",
        "15943975768656639571982891693993452034850168468307",
        "13339142397055768569132275120592606565814175467126",
        "87185744974336622831854423410192940914726425360946",
        "70483889554282793297509515736916671273381776857529",
        "82872282685498103884986533620480099395352356530285",
        "09349007115178576504993149187241028262848399118108",
        "68539240109135037448704278992835621172827346689353",
        "92855271502419195917337257023516846859260060551568",
        "83965007941712923530678439551199466451770788839617",
        "40677383449278717467005659412642648662867507007345",
        "54159297771255873049643609119134482865780145628235",
        "12705385258801765651836528057017069200052527232163",
        "54063632277863256281270601193374467901427167567854",
        "21496933706878231890212670284406606815850960732471",
        "29698621504965516019111806482391603868081406624118",
        "38494036524685051239294074081914688382715452343915",
        "19604365923740039644993081972710267053484612276426",
        "90282970179192492260775098041549752180968344423751",
        "62128639303380544896944704526819037787652578673055",
        "51564957343579218676784342169168645103352848363381",
        "45966775291210271782845558612510209487829578268308",
        "18579746879072559094465865304741630139975733828187",
        "48906860879414473813902993535524879863400102362761",
        "03084809557657446372359781288099719777092189030484",
        "23305139602342425816144587071545811729315578968078",
        "01274453262367673566962947070128763565759860495995",
        "58078933624036739666193790779524749625697605939796",
        "17210051306728161143756372499311258099280748625014",
        "57340064789182075521593994190075808010516370687356",
        "70373725524792628945187532123962371743471353092853",
        "57257810476177347565138676066964950350156795735949",
        "17209107784011813991831786667191692233717520820988",
        "62566823616010436452529908687631030087067208676252",
        "26955264704139973263608564992658550779404581207263",
        "14171901822332964275266456329777947113280968447042",
        "30433352058283683929806796660879588230179188203419",
        "07409002486463886816550051812951872161087556031443",
        "38548783663055278424896919732678403461827118035032",
        "07437714418126442153383102042401820945123969678411",
        "33546768421552252212281678589466695263609499238736",
        "22885001325980095931990427591421344589617968102776",
        "47781286835914618494269769223518702536200355284559",
        "63259970546079676842165430842401132758223172358067",
        "76927562301942050262983556867248619211453524247773",
        "22569585070229036456285284235658257652757231910732",
        "10554756743598849914374157362131913385227206889792",
        "51797889730412731777062772865848988297845410759481",
        "18315662237319431544184308512772537413038730289283",
        "93596822115229372013422561987208181999192834592843",
        "53639597895193945695000144083523623250466035975904",
        "30948588308530839638112155224670317320558125164792",
        "22916923539975198642487663285168177927022261189614",
        "75479532559809320184057270177834096210449175976426",
        "91576992110903597922935940550516051974527760798132",
        "27657707770490092830215299048592541357852288088168",
        "80377085074654804320537833561838442740380793760311",
        "18562174501319457811092178180089136304176747195928",
        "00500436579827566362943365451596268381844013332679",
        "72305215272212554128852493813872507071538108264824",
        "98779869219615725672821256126718500218964530612155",
        "68899325338856754963870910573464993392343759183223",
        "73310792975372519016873886183708157748156946160557",
        "13721337139938944086193699324910432629125724877126",
        "40577641953051906643678647661966594374170758142923",
        "22662691631961152332420109849882691253203417681599",
        "42704544964960253586829389703817474519500806476237",
        "81841265555084337228972463041516171447642522814867",
        "25867088062897122498939861540274689524301971624179",
        "09024628981033336390870345776731364399728164638778",
        "68725967821832234538858102151238807647612520884801",
        "93087836791636301394090039963683546428747421692317",
        "61111080472315693380839353260432249799327537048126",
        "11415809448903003244167867814979778088418919872666",
        "41709796098901153308193297744746763828639262816606",
        "69059754667995638067552474404635609925598044968758",
        "79203279109499574067991289102170698350990469342066",
        "25298058066558730977314002173065137923008628931946",
        "11051325624031493570730960986457205727891393903761",
        "19763489501745736854612900145905159784054277390849",
        "99600382099577796971914600759913429478112076193687",
        "87033794445701487208367850311825941663911731786351",
        "35371988424458633055232422324116526553551132998704",
        "53594140239122327606936086096302084604410511998844",
        "45913666505601777960086304399235063593308882130514",
        "08230722872630418543975586585093764101237608843218",
        "80603252321549052560714954823229572384937707561628",
        "79111808916692427088808105493891791377785020881922",
        "71695812784987728868790854231409054561020524585177",
        "61590548229637475226048826653455168196053483870127",
        "22790640825254255532866617603932710043108930694802",
        "09613303346218798719557045047805242527462243530535"
    };

    constexpr LargeNumber answer = sum(numbers);
    for (auto c = answer.rbegin(); c != answer.rbegin() + 10; ++c)
        std::cout << *c;
    std::cout << std::endl;

    return 0;
}