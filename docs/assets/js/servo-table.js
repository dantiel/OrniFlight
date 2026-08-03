// OrniFlight Servo Efficiency — Sortable Table + Currency Converter + Voltage Filter
;(function () {
  'use strict'

  var RATES = {
    EUR: 1.0,
    USD: 1.08,
    GBP: 0.85,
    CHF: 0.94,
    JPY: 156.0,
    BRL: 5.8,
  }

  var SYMBOLS = {
    EUR: '€',
    USD: '$',
    GBP: '£',
    CHF: 'CHF',
    JPY: '¥',
    BRL: 'R$',
  }

  var CURRENCY_NAMES = {
    EUR: 'Euro',
    USD: 'Dollar',
    GBP: 'Pound',
    CHF: 'Franc',
    JPY: 'Yen',
    BRL: 'Real',
  }

  function detectLocale() {
    var lang = (navigator.language || 'en').toLowerCase()
    if (lang.indexOf('de') === 0 || lang.indexOf('at') === 0) return 'EUR'
    if (lang.indexOf('ch') === 0) return 'CHF'
    if (lang.indexOf('jp') === 0) return 'JPY'
    if (lang.indexOf('br') === 0) return 'BRL'
    if (lang.indexOf('gb') === 0) return 'GBP'
    if (lang.indexOf('us') === 0) return 'USD'
    return 'EUR'
  }

  var table = document.querySelector('.servo-table')
  if (!table) return

  var thead = table.querySelector('thead')
  var tbody = table.querySelector('tbody')
  var headers = thead.querySelectorAll('th')

  // ── Currency ─────────────────────────────────────────────
  var currencySelect = document.querySelector('.currency-select')
  var currentCurrency = localStorage.getItem('orni-currency') || detectLocale()

  if (currencySelect) {
    currencySelect.value = currentCurrency
    currencySelect.addEventListener('change', function () {
      currentCurrency = this.value
      localStorage.setItem('orni-currency', currentCurrency)
      convertPrices()
    })
  }

  function convertPrices() {
    var rate = RATES[currentCurrency] || 1.0
    var sym = SYMBOLS[currentCurrency] || '€'
    tbody.querySelectorAll('td[data-price-eur]').forEach(function (cell) {
      var eur = parseFloat(cell.getAttribute('data-price-eur'))
      if (isNaN(eur)) return
      var converted = eur * rate
      cell.textContent =
        currentCurrency === 'JPY'
          ? sym + Math.round(converted).toLocaleString()
          : sym + converted.toFixed(2)
    })

    // Update currency symbols everywhere
    document.querySelectorAll('.currency-symbol').forEach(function (el) {
      el.textContent = sym
    })

    // Refresh option display names
    if (currencySelect) {
      Array.prototype.forEach.call(currencySelect.options, function (opt) {
        opt.textContent = CURRENCY_NAMES[opt.value] || opt.value
      })
    }
  }

  // ── Voltage Range Slider ─────────────────────────────────
  var vrMin  = document.querySelector('.vr-min')
  var vrMax  = document.querySelector('.vr-max')
  var vrRead = document.querySelector('.vr-readout')
  var vrTrack = document.querySelector('.vr-track')

  if (vrMin && vrMax) {
    function clampVoltage(v) {
      return Math.round(v * 10) / 10
    }

    function updateVoltageRange() {
      var minV = parseFloat(vrMin.value)
      var maxV = parseFloat(vrMax.value)

      // Prevent crossover
      if (minV > maxV) {
        var tmp = minV; minV = maxV; maxV = tmp
        vrMin.value = minV
        vrMax.value = maxV
      }

      // Update readout
      if (vrRead) {
        vrRead.textContent = clampVoltage(minV) + 'V \u2013 ' + clampVoltage(maxV) + 'V'
      }

      // Update fill track
      var rangeSpan = 8.4 - 4.8
      var leftPct  = ((minV - 4.8) / rangeSpan) * 100
      var rightPct = ((8.4 - maxV) / rangeSpan) * 100
      if (vrTrack) {
        vrTrack.style.setProperty('--vr-left',  leftPct  + '%')
        vrTrack.style.setProperty('--vr-right', rightPct + '%')
      }

      // Filter rows
      tbody.querySelectorAll('tr').forEach(function (row) {
        var v = parseFloat(row.getAttribute('data-voltage'))
        row.style.display = (!isNaN(v) && v >= minV - 0.01 && v <= maxV + 0.01) ? '' : 'none'
      })
    }

    vrMin.addEventListener('input', updateVoltageRange)
    vrMax.addEventListener('input', updateVoltageRange)
    updateVoltageRange() // initial fill track + readout
  }

  // ── Multi-Column Sort (Shift+click for additive) ─────────
  var sortState = []  // [{col, dir}, ...] — most significant first

  headers.forEach(function (th, i) {
    var indicator = document.createElement('span')
    indicator.className = 'sort-order'
    th.appendChild(indicator)

    th.addEventListener('click', function (e) {
      if (e.shiftKey) {
        // Toggle through: not present → asc → desc → remove
        var idx = -1
        for (var s = 0; s < sortState.length; s++) {
          if (sortState[s].col === i) { idx = s; break }
        }
        if (idx >= 0) {
          if (sortState[idx].dir === 'asc') {
            sortState[idx].dir = 'desc'
          } else {
            sortState.splice(idx, 1)
          }
        } else {
          sortState.push({col: i, dir: 'asc'})
        }
      } else {
        // Single-column: toggle asc/desc, replace state
        var wasSame = sortState.length === 1 && sortState[0].col === i
        sortState.length = 0
        sortState.push({col: i, dir: wasSame && getPrevDir(i) === 'asc' ? 'desc' : 'asc'})
      }
      updateIndicator()
      doSort()
    })
    th.classList.add('sortable')
  })

  function getPrevDir(col) {
    // Used only for single-column toggle before state was cleared
    var th = headers[col]
    if (th.classList.contains('sort-asc')) return 'asc'
    if (th.classList.contains('sort-desc')) return 'desc'
    return ''
  }

  function updateIndicator() {
    headers.forEach(function (th) {
      th.classList.remove('sort-asc', 'sort-desc')
      var ind = th.querySelector('.sort-order')
      if (ind) ind.textContent = ''
    })
    for (var s = 0; s < sortState.length; s++) {
      var st = sortState[s]
      var th = headers[st.col]
      th.classList.add(st.dir === 'asc' ? 'sort-asc' : 'sort-desc')
      var ind = th.querySelector('.sort-order')
      if (ind && sortState.length > 1) {
        ind.textContent = s + 1
      }
    }
  }

  function getCellValue(cell, colIndex) {
    if (colIndex === 6) {
      // Price — use data attribute
      return parseFloat(cell.getAttribute('data-price-eur')) || 0
    }
    if (colIndex === 8) {
      // Flight Performance — use rating
      return parseInt(cell.getAttribute('data-flight-rating')) || 0
    }
    // Numeric columns: 1(V), 2(Weight), 3(Torque), 4(Speed), 5(Efficiency), 7(Eff/€)
    if (colIndex >= 1 && colIndex <= 7) {
      return parseFloat(cell.textContent.replace(/[^0-9.\-]/g, '')) || 0
    }
    // String columns: 0(Servo), 9(Notes)
    return (cell.textContent || '').trim().toLowerCase()
  }

  function doSort() {
    var rows = Array.prototype.slice.call(tbody.querySelectorAll('tr'))
    if (sortState.length === 0) return

    // Cascading stable sort: least significant first, most significant last
    for (var s = sortState.length - 1; s >= 0; s--) {
      var col = sortState[s].col
      var dir = sortState[s].dir
      var isNumeric = col >= 1 && col <= 8

      rows.sort(function (a, b) {
        var aCell = a.children[col]
        var bCell = b.children[col]
        if (!aCell || !bCell) return 0
        var aVal = getCellValue(aCell, col)
        var bVal = getCellValue(bCell, col)

        if (isNumeric) {
          var diff = aVal - bVal
          return dir === 'asc' ? diff : -diff
        } else {
          var cmp = String(aVal).localeCompare(String(bVal))
          return dir === 'asc' ? cmp : -cmp
        }
      })
    }

    var frag = document.createDocumentFragment()
    for (var r = 0; r < rows.length; r++) {
      frag.appendChild(rows[r])
    }
    tbody.appendChild(frag)
  }

  // ── Rating Classes ───────────────────────────────────────
  tbody.querySelectorAll('td[data-flight-rating]').forEach(function (cell) {
    var r = parseInt(cell.getAttribute('data-flight-rating'))
    if (r >= 1 && r <= 5) cell.classList.add('fp-' + r)
  })

  // Initial conversion
  if (currentCurrency !== 'EUR') convertPrices()
})()