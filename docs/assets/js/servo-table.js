// OrniFlight Servo Efficiency — Sortable Table + Currency Converter
;(function () {
  'use strict'

  const RATES = {
    EUR: 1.0,
    USD: 1.08,
    GBP: 0.85,
    CHF: 0.94,
    JPY: 156.0,
    BRL: 5.8,
  }

  const SYMBOLS = {
    EUR: '€',
    USD: '$',
    GBP: '£',
    CHF: 'CHF',
    JPY: '¥',
    BRL: 'R$',
  }

  const table = document.querySelector('.servo-table')
  if (!table) return

  const thead = table.querySelector('thead')
  const tbody = table.querySelector('tbody')
  const headers = thead.querySelectorAll('th')

  // ── Currency ──────────────────────────────────────────────
  const currencySelect = document.querySelector('.currency-select')
  let currentCurrency = localStorage.getItem('orni-currency') || 'EUR'

  if (currencySelect) {
    currencySelect.value = currentCurrency
    currencySelect.addEventListener('change', function () {
      currentCurrency = this.value
      localStorage.setItem('orni-currency', currentCurrency)
      convertPrices()
    })
  }

  function convertPrices() {
    const rate = RATES[currentCurrency] || 1.0
    const sym = SYMBOLS[currentCurrency] || '€'
    tbody.querySelectorAll('td[data-price-eur]').forEach(function (cell) {
      const eur = parseFloat(cell.getAttribute('data-price-eur'))
      if (isNaN(eur)) return
      const converted = eur * rate
      cell.textContent =
        currentCurrency === 'JPY'
          ? sym + Math.round(converted).toLocaleString()
          : sym + converted.toFixed(2)
    })
  }

  // ── Sort ──────────────────────────────────────────────────
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
    'string',
    'string',
  ]

  var sortState = {} // {colIndex: 'asc'|'desc'}

  headers.forEach(function (th, i) {
    th.addEventListener('click', function () {
      sortTable(i)
    })
    th.classList.add('sortable')
  })

  function sortTable(colIndex) {
    var dir = sortState[colIndex] === 'asc' ? 'desc' : 'asc'
    sortState = {}
    sortState[colIndex] = dir

    headers.forEach(function (h, i) {
      h.classList.remove('sort-asc', 'sort-desc')
      if (i === colIndex) h.classList.add(dir === 'asc' ? 'sort-asc' : 'sort-desc')
    })

    var rows = Array.from(tbody.querySelectorAll('tr'))
    var type = COL_TYPES[colIndex] || 'string'

    rows.sort(function (a, b) {
      var aCell = a.children[colIndex]
      var bCell = b.children[colIndex]
      if (!aCell || !bCell) return 0

      var aVal, bVal

      if (type === 'price') {
        aVal = parseFloat(aCell.getAttribute('data-price-eur')) || 0
        bVal = parseFloat(bCell.getAttribute('data-price-eur')) || 0
      } else if (type === 'number') {
        aVal = parseFloat(aCell.textContent.replace(/[^0-9.\-]/g, ''))
        bVal = parseFloat(bCell.textContent.replace(/[^0-9.\-]/g, ''))
        if (isNaN(aVal)) aVal = 0
        if (isNaN(bVal)) bVal = 0
      } else {
        aVal = aCell.textContent.trim().toLowerCase()
        bVal = bCell.textContent.trim().toLowerCase()
        if (dir === 'asc') return aVal.localeCompare(bVal)
        return bVal.localeCompare(aVal)
      }

      if (dir === 'asc') return aVal - bVal
      return bVal - aVal
    })

    rows.forEach(function (row) {
      tbody.appendChild(row)
    })
  }

  // Initial conversion
  if (currentCurrency !== 'EUR') convertPrices()
})()
