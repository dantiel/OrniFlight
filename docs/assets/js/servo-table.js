// OrniFlight Servo Efficiency — Multi-Sort Table + Currency Converter
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

  var ORDER_CHARS = ['①', '②', '③', '④', '⑤']

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

  // ── Currency ──────────────────────────────────────────────
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
  }

  // ── Multi-Column Sort ─────────────────────────────────────
  // Column types: 0=Servo(string) 1=V(number) 2=Weight 3=Torque 4=Speed 5=Efficiency 6=Price 7=Eff/€ 8=Flight 9=Notes
  var COL_TYPES = [
    'string',
    'number',
    'number',
    'number',
    'number',
    'number',
    'price',
    'number',
    'rating',
    'string',
  ]

  var sortState = [] // [{col: 0, dir: 'asc'}, ...]

  // Inject sort-order indicator spans
  headers.forEach(function (th) {
    var indicator = document.createElement('span')
    indicator.className = 'sort-order'
    th.appendChild(indicator)
  })

  headers.forEach(function (th, i) {
    th.addEventListener('click', function (e) {
      sortTable(i, e.shiftKey)
    })
    th.classList.add('sortable')
  })

  function sortTable(colIndex, additive) {
    var existingIdx = -1
    for (var i = 0; i < sortState.length; i++) {
      if (sortState[i].col === colIndex) { existingIdx = i; break }
    }

    if (additive) {
      if (existingIdx >= 0) {
        // Toggle direction in place
        sortState[existingIdx].dir = sortState[existingIdx].dir === 'asc' ? 'desc' : 'asc'
      } else {
        // Append to chain
        sortState.push({col: colIndex, dir: 'asc'})
      }
    } else {
      if (sortState.length === 1 && sortState[0].col === colIndex) {
        // Toggle single column
        sortState[0].dir = sortState[0].dir === 'asc' ? 'desc' : 'asc'
      } else {
        // Replace with single column
        sortState = [{col: colIndex, dir: 'asc'}]
      }
    }

    updateIndicators()
    doSort()
  }

  function updateIndicators() {
    headers.forEach(function (th) {
      th.classList.remove('sort-asc', 'sort-desc')
      var ind = th.querySelector('.sort-order')
      if (ind) ind.textContent = ''
    })
    sortState.forEach(function (s, idx) {
      var th = headers[s.col]
      th.classList.add(s.dir === 'asc' ? 'sort-asc' : 'sort-desc')
      var ind = th.querySelector('.sort-order')
      if (ind && idx < ORDER_CHARS.length) {
        ind.textContent = ORDER_CHARS[idx]
      }
    })
  }

  function doSort() {
    var rows = Array.from(tbody.querySelectorAll('tr'))

    rows.sort(function (a, b) {
      for (var i = 0; i < sortState.length; i++) {
        var s = sortState[i]
        var result = compareCells(a.children[s.col], b.children[s.col], s.col, s.dir)
        if (result !== 0) return result
      }
      return 0
    })

    rows.forEach(function (row) {
      tbody.appendChild(row)
    })
  }

  function compareCells(aCell, bCell, colIndex, dir) {
    if (!aCell || !bCell) return 0
    var type = COL_TYPES[colIndex] || 'string'
    var aVal, bVal

    if (type === 'price') {
      aVal = parseFloat(aCell.getAttribute('data-price-eur')) || 0
      bVal = parseFloat(bCell.getAttribute('data-price-eur')) || 0
    } else if (type === 'rating') {
      aVal = parseInt(aCell.getAttribute('data-flight-rating')) || 0
      bVal = parseInt(bCell.getAttribute('data-flight-rating')) || 0
    } else if (type === 'number') {
      aVal = parseFloat(aCell.textContent.replace(/[^0-9.\-]/g, ''))
      bVal = parseFloat(bCell.textContent.replace(/[^0-9.\-]/g, ''))
      if (isNaN(aVal)) aVal = 0
      if (isNaN(bVal)) bVal = 0
    } else {
      aVal = aCell.textContent.trim().toLowerCase()
      bVal = bCell.textContent.trim().toLowerCase()
      var cmp = aVal.localeCompare(bVal)
      return dir === 'asc' ? cmp : -cmp
    }

    var diff = aVal - bVal
    return dir === 'asc' ? diff : -diff
  }

  // ── Apply rating classes ──────────────────────────────────
  tbody.querySelectorAll('td[data-flight-rating]').forEach(function (cell) {
    var r = parseInt(cell.getAttribute('data-flight-rating'))
    if (r >= 1 && r <= 5) cell.classList.add('fp-' + r)
  })

  // Initial conversion
  if (currentCurrency !== 'EUR') convertPrices()
})()