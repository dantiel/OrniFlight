# Servo-Effizienz

Eine kuratierte Auswahl getesteter Servos für Ornithopter.
**Effizienz** = Drehmoment / (Gewicht × Geschwindigkeit). **Eff/€ ★** = Effizienz pro Euro, skaliert mit &cuberoot;Drehmoment.
Höher ist besser. Fluggetestete Einträge mit Praxisergebnissen.

Spaltenköpfe anklicken zum Sortieren. Ergänzungen per PR an `_data/servos.yml`.


<div class="currency-bar">
  <label for="currency-select">Currency</label>
  <select id="currency-select" class="currency-select">
    <option value="EUR">EUR €</option>
    <option value="USD">USD $</option>
    <option value="GBP">GBP £</option>
    <option value="CHF">CHF</option>
    <option value="JPY">JPY ¥</option>
    <option value="BRL">BRL R$</option>
  </select>
</div>

<table class="servo-table">
  <thead>
    <tr>
      <th>Servo</th>
      <th class="num">V</th>
      <th class="num">Weight g</th>
      <th class="num">Torque kg/cm</th>
      <th class="num">Speed s/60°</th>
      <th class="num">Efficiency</th>
      <th class="num">Price</th>
      <th class="num">Eff/€ ★</th>
      <th>Flight Performance</th>
      <th>Notes</th>
    </tr>
  </thead>
  <tbody>
      <tr>
        <td>KST DS 113 MG</td>
        <td class="num">4.8</td>
        <td class="num">12.0</td>
        <td class="num">1.80</td>
        <td class="num">0.14</td>
        <td class="num">1.07</td>
        <td class="num" data-price-eur="14.30">€14.30</td>
        <td class="num strong">0.09</td>
        <td class="flight"></td>
        <td class="notes"></td>
      </tr>
      <tr>
        <td>Blue Arrow D05023MG</td>
        <td class="num">4.8</td>
        <td class="num">5.4</td>
        <td class="num">1.50</td>
        <td class="num">0.06</td>
        <td class="num">4.63</td>
        <td class="num" data-price-eur="12.00">€12.00</td>
        <td class="num strong">0.44</td>
        <td class="flight"></td>
        <td class="notes">Slow under load</td>
      </tr>
      <tr>
        <td>Blue Arrow D43S-6.0-MG</td>
        <td class="num">5.0</td>
        <td class="num">5.6</td>
        <td class="num">1.48</td>
        <td class="num">0.05</td>
        <td class="num">5.51</td>
        <td class="num" data-price-eur="11.00">€11.00</td>
        <td class="num strong">0.57</td>
        <td class="flight"></td>
        <td class="notes"></td>
      </tr>
      <tr>
        <td>Blue Arrow D05023MG</td>
        <td class="num">5.0</td>
        <td class="num">5.4</td>
        <td class="num">1.23</td>
        <td class="num">0.04</td>
        <td class="num">5.06</td>
        <td class="num" data-price-eur="12.00">€12.00</td>
        <td class="num strong">0.45</td>
        <td class="flight"></td>
        <td class="notes"></td>
      </tr>
      <tr>
        <td>Blue Arrow AF D43S-6.0-MG</td>
        <td class="num">6.0</td>
        <td class="num">5.6</td>
        <td class="num">1.76</td>
        <td class="num">0.04</td>
        <td class="num">7.67</td>
        <td class="num" data-price-eur="11.00">€11.00</td>
        <td class="num strong">0.84</td>
        <td class="flight" data-flight-rating="4">Good Flight</td>
        <td class="notes">Up to 6.2V</td>
      </tr>
      <tr>
        <td>Blue Arrow D05023MG</td>
        <td class="num">6.0</td>
        <td class="num">5.4</td>
        <td class="num">1.42</td>
        <td class="num">0.04</td>
        <td class="num">6.57</td>
        <td class="num" data-price-eur="12.00">€12.00</td>
        <td class="num strong">0.62</td>
        <td class="flight"></td>
        <td class="notes"></td>
      </tr>
      <tr>
        <td>KST DS 113 MG</td>
        <td class="num">6.0</td>
        <td class="num">12.0</td>
        <td class="num">2.20</td>
        <td class="num">0.11</td>
        <td class="num">1.67</td>
        <td class="num" data-price-eur="14.30">€14.30</td>
        <td class="num strong">0.15</td>
        <td class="flight"></td>
        <td class="notes"></td>
      </tr>
      <tr>
        <td>Spektrum H2060</td>
        <td class="num">6.0</td>
        <td class="num">4.0</td>
        <td class="num">0.82</td>
        <td class="num">0.07</td>
        <td class="num">2.93</td>
        <td class="num" data-price-eur="16.00">€16.00</td>
        <td class="num strong">0.17</td>
        <td class="flight"></td>
        <td class="notes">Ultra-light 4g</td>
      </tr>
      <tr>
        <td>Blue Arrow D03013</td>
        <td class="num">6.0</td>
        <td class="num">3.0</td>
        <td class="num">0.65</td>
        <td class="num">0.06</td>
        <td class="num">3.61</td>
        <td class="num" data-price-eur="13.10">€13.10</td>
        <td class="num strong">0.24</td>
        <td class="flight"></td>
        <td class="notes">Ultra-light 3g</td>
      </tr>
      <tr>
        <td>VOTIK PTK 7350 MG-D</td>
        <td class="num">7.4</td>
        <td class="num">5.5</td>
        <td class="num">1.80</td>
        <td class="num">0.07</td>
        <td class="num">4.68</td>
        <td class="num" data-price-eur="5.50">€5.50</td>
        <td class="num strong">1.03</td>
        <td class="flight"></td>
        <td class="notes">Best efficiency/€ — the budget king</td>
      </tr>
      <tr>
        <td>Inservos D0576HT-MG-HV</td>
        <td class="num">7.4</td>
        <td class="num">7.9</td>
        <td class="num">4.20</td>
        <td class="num">0.06</td>
        <td class="num">9.49</td>
        <td class="num" data-price-eur="20.00">€20.00</td>
        <td class="num strong">0.77</td>
        <td class="flight" data-flight-rating="5">Strong Flight</td>
        <td class="notes">Gear broke on first test flight</td>
      </tr>
      <tr>
        <td>Inservos D0474HT-MG-HV</td>
        <td class="num">7.4</td>
        <td class="num">7.3</td>
        <td class="num">3.60</td>
        <td class="num">0.08</td>
        <td class="num">6.16</td>
        <td class="num" data-price-eur="23.00">€23.00</td>
        <td class="num strong">0.41</td>
        <td class="flight" data-flight-rating="3">Okay Flight</td>
        <td class="notes"></td>
      </tr>
      <tr>
        <td>Blue Bird BMS-126WV</td>
        <td class="num">7.4</td>
        <td class="num">11.3</td>
        <td class="num">6.50</td>
        <td class="num">0.07</td>
        <td class="num">8.22</td>
        <td class="num" data-price-eur="20.00">€20.00</td>
        <td class="num strong">0.77</td>
        <td class="flight"></td>
        <td class="notes">New 2024 WV series</td>
      </tr>
      <tr>
        <td>Blue Bird BMS-127WV</td>
        <td class="num">7.4</td>
        <td class="num">11.3</td>
        <td class="num">4.80</td>
        <td class="num">0.05</td>
        <td class="num">8.50</td>
        <td class="num" data-price-eur="20.00">€20.00</td>
        <td class="num strong">0.72</td>
        <td class="flight"></td>
        <td class="notes">New WV series, slower but precise</td>
      </tr>
      <tr>
        <td>Blue Bird BMS-115WV</td>
        <td class="num">7.4</td>
        <td class="num">11.1</td>
        <td class="num">7.10</td>
        <td class="num">0.09</td>
        <td class="num">7.11</td>
        <td class="num" data-price-eur="20.00">€20.00</td>
        <td class="num strong">0.68</td>
        <td class="flight"></td>
        <td class="notes"></td>
      </tr>
      <tr>
        <td>Blue Bird BMS-125WV</td>
        <td class="num">7.4</td>
        <td class="num">11.3</td>
        <td class="num">7.10</td>
        <td class="num">0.09</td>
        <td class="num">6.98</td>
        <td class="num" data-price-eur="20.00">€20.00</td>
        <td class="num strong">0.67</td>
        <td class="flight"></td>
        <td class="notes">Like 115WV, sub-zero rated</td>
      </tr>
      <tr>
        <td>Blue Bird BMS-207WV</td>
        <td class="num">7.4</td>
        <td class="num">17.5</td>
        <td class="num">7.50</td>
        <td class="num">0.05</td>
        <td class="num">8.57</td>
        <td class="num" data-price-eur="25.00">€25.00</td>
        <td class="num strong">0.67</td>
        <td class="flight"></td>
        <td class="notes"></td>
      </tr>
      <tr>
        <td>Blue Bird BMS-M15S</td>
        <td class="num">7.4</td>
        <td class="num">13.8</td>
        <td class="num">7.50</td>
        <td class="num">0.10</td>
        <td class="num">5.43</td>
        <td class="num" data-price-eur="16.00">€16.00</td>
        <td class="num strong">0.66</td>
        <td class="flight"></td>
        <td class="notes">Great value mid-weight</td>
      </tr>
      <tr>
        <td>Blue Bird BMS-115HV</td>
        <td class="num">7.4</td>
        <td class="num">11.3</td>
        <td class="num">5.40</td>
        <td class="num">0.10</td>
        <td class="num">4.78</td>
        <td class="num" data-price-eur="18.00">€18.00</td>
        <td class="num strong">0.47</td>
        <td class="flight"></td>
        <td class="notes"></td>
      </tr>
      <tr>
        <td>Blue Bird BMS-107HV</td>
        <td class="num">7.4</td>
        <td class="num">10.5</td>
        <td class="num">2.50</td>
        <td class="num">0.05</td>
        <td class="num">4.76</td>
        <td class="num" data-price-eur="13.00">€13.00</td>
        <td class="num strong">0.50</td>
        <td class="flight"></td>
        <td class="notes">Entry-level WV</td>
      </tr>
      <tr>
        <td>Blue Bird A10H WV</td>
        <td class="num">7.4</td>
        <td class="num">7.4</td>
        <td class="num">3.20</td>
        <td class="num">0.07</td>
        <td class="num">6.18</td>
        <td class="num" data-price-eur="33.00">€33.00</td>
        <td class="num strong">0.28</td>
        <td class="flight"></td>
        <td class="notes"></td>
      </tr>
      <tr>
        <td>JX DHV56MG</td>
        <td class="num">7.4</td>
        <td class="num">5.6</td>
        <td class="num">1.20</td>
        <td class="num">0.10</td>
        <td class="num">2.14</td>
        <td class="num" data-price-eur="8.15">€8.15</td>
        <td class="num strong">0.28</td>
        <td class="flight"></td>
        <td class="notes">Budget 5.6g option</td>
      </tr>
      <tr>
        <td>KST MR320</td>
        <td class="num">7.4</td>
        <td class="num">21.0</td>
        <td class="num">5.50</td>
        <td class="num">0.08</td>
        <td class="num">3.27</td>
        <td class="num" data-price-eur="36.00">€36.00</td>
        <td class="num strong">0.16</td>
        <td class="flight" data-flight-rating="4">Good Flight</td>
        <td class="notes">Magnet potentiometer</td>
      </tr>
      <tr>
        <td>KST X08 Plus V5</td>
        <td class="num">7.4</td>
        <td class="num">9.0</td>
        <td class="num">4.85</td>
        <td class="num">0.12</td>
        <td class="num">4.49</td>
        <td class="num" data-price-eur="43.00">€43.00</td>
        <td class="num strong">0.18</td>
        <td class="flight"></td>
        <td class="notes">Premium 9g, excellent build</td>
      </tr>
      <tr>
        <td>KST DS215MG</td>
        <td class="num">7.4</td>
        <td class="num">20.0</td>
        <td class="num">3.70</td>
        <td class="num">0.05</td>
        <td class="num">3.70</td>
        <td class="num" data-price-eur="33.50">€33.50</td>
        <td class="num strong">0.17</td>
        <td class="flight"></td>
        <td class="notes"></td>
      </tr>
      <tr>
        <td>SAVÖX SV-1232MG</td>
        <td class="num">7.4</td>
        <td class="num">23.0</td>
        <td class="num">5.00</td>
        <td class="num">0.05</td>
        <td class="num">4.35</td>
        <td class="num" data-price-eur="23.00">€23.00</td>
        <td class="num strong">0.32</td>
        <td class="flight"></td>
        <td class="notes"></td>
      </tr>
      <tr>
        <td>Blue Arrow MI CS 9-6F MG</td>
        <td class="num">7.4</td>
        <td class="num">7.6</td>
        <td class="num">2.68</td>
        <td class="num">0.05</td>
        <td class="num">7.46</td>
        <td class="num" data-price-eur="19.50">€19.50</td>
        <td class="num strong">0.53</td>
        <td class="flight"></td>
        <td class="notes">Magnet potentiometer</td>
      </tr>
      <tr>
        <td>Blue Arrow MI CS 9-6 MG</td>
        <td class="num">7.4</td>
        <td class="num">7.9</td>
        <td class="num">3.60</td>
        <td class="num">0.07</td>
        <td class="num">6.24</td>
        <td class="num" data-price-eur="19.50">€19.50</td>
        <td class="num strong">0.49</td>
        <td class="flight"></td>
        <td class="notes">Magnet potentiometer</td>
      </tr>
      <tr>
        <td>ROBSG HS1106S</td>
        <td class="num">7.4</td>
        <td class="num">20.3</td>
        <td class="num">9.50</td>
        <td class="num">0.05</td>
        <td class="num">9.36</td>
        <td class="num" data-price-eur="28.00">€28.00</td>
        <td class="num strong">0.71</td>
        <td class="flight"></td>
        <td class="notes">Gear failure after few flights</td>
      </tr>
      <tr>
        <td>DUALSKY DS169F</td>
        <td class="num">7.4</td>
        <td class="num">9.0</td>
        <td class="num">2.80</td>
        <td class="num">0.06</td>
        <td class="num">5.19</td>
        <td class="num" data-price-eur="30.99">€30.99</td>
        <td class="num strong">0.24</td>
        <td class="flight"></td>
        <td class="notes"></td>
      </tr>
      <tr>
        <td>Petoi P1S</td>
        <td class="num">7.4</td>
        <td class="num">14.0</td>
        <td class="num">3.00</td>
        <td class="num">0.07</td>
        <td class="num">3.06</td>
        <td class="num" data-price-eur="14.00">€14.00</td>
        <td class="num strong">0.32</td>
        <td class="flight"></td>
        <td class="notes"></td>
      </tr>
      <tr>
        <td>Blue Arrow X-4 HTMG HV</td>
        <td class="num">8.4</td>
        <td class="num">7.3</td>
        <td class="num">3.40</td>
        <td class="num">0.04</td>
        <td class="num">10.83</td>
        <td class="num"></td>
        <td class="num strong"></td>
        <td class="flight"></td>
        <td class="notes">Highest raw efficiency in class; factory price only</td>
      </tr>
      <tr>
        <td>HDKJ D3625MG</td>
        <td class="num">7.4</td>
        <td class="num">67.0</td>
        <td class="num">26.00</td>
        <td class="num">0.07</td>
        <td class="num">5.54</td>
        <td class="num" data-price-eur="21.00">€21.00</td>
        <td class="num strong">0.78</td>
        <td class="flight"></td>
        <td class="notes">Waterproof; large but excellent value</td>
      </tr>
  </tbody>
</table>
<script src="../../assets/js/servo-table.js"></script>

