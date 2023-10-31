//https://api.thingspeak.com/channels/2293246/fields/1.json?api_key=75G28B9ZTDU5N8S5&results=1

// ThingSpeak data
const READ_API_KEY = '75G28B9ZTDU5N8S5'
const CHANNEL_ID = 2293246
const FIELD_POTENCIA = 2
const FIELD_CORRIENTE = 3

const chartPot = new Chart(potencia, {
    type: 'line',
    data: {
        labels: ['-30 sec', '-27 sec', '-24 sec',
                 '-21 sec', '-18 sec', '-15 sec',
                 '-12 sec', '-9 sec', '-6 sec',
                 '-3 sec', '0 sec'],
        datasets: [{
            label: 'Vatios',
            data: [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
            borderWidth: 2,
            borderColor: 'rgba(120, 120, 250)'
        }]
    },
    options: {
        scales: {
            y: {
                beginAtZero: true
            }
        }
    }
})

const chartCor = new Chart(corriente, {
    type: 'line',
    data: {
        labels: ['-30 sec', '-27 sec', '-24 sec',
                 '-21 sec', '-18 sec', '-15 sec',
                 '-12 sec', '-9 sec', '-6 sec',
                 '-3 sec', '0 sec'],
        datasets: [{
            label: 'mA',
            data: [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
            borderWidth: 1,
            borderColor: 'rgba(200, 30, 250)'
        }]
    },
    options: {
        scales: {
            y: {
                beginAtZero: true
            }
        }
    }
})

function addNewData(chart, newData) {
    chart.data.datasets.forEach((dataset) => {
        dataset.data.push(newData)
    })
    chart.update()
}

function removeOldData(chart) {
    chart.data.datasets.forEach((dataset) => {
        dataset.data.shift()
    });
    chart.update()
}

function newURL(field, results) {
    return `https://api.thingspeak.com/channels/${CHANNEL_ID}/fields/${field}.json?api_key=${READ_API_KEY}&results=${results}`
}

async function getLastValue(field) {
	let res = await fetch(newURL(field, 1))
	let json = await res.json()
	let v = parseInt(json["feeds"]["0"][`field${field}`])

	if (isNaN(v)) {
		v = 0
	}

	return {
        value: v,
        entryId: json["feeds"]["0"]["entry_id"]
    }
}

async function updateChart(fieldId, chart) {
    const field = await getLastValue(fieldId)

    if (!chart.lastEntryId) {
        chart.lastEntryId = -1
    }

    if (field.entryId !== chart.lastEntryId) {
        removeOldData(chart)
        addNewData(chart, field.value)
    }
}

function startUpdating() {
    return setInterval(() => {
        updateChart(FIELD_POTENCIA, chartPot)
        updateChart(FIELD_CORRIENTE, chartCor)
    }, 3000)
}

updateButton.addEventListener('click', () => {
    if (updatingInterval) {
        clearInterval(updatingInterval)
        updatingInterval = null
        updateButton.textContent = 'Empezar a actualizar'
    } else {
        updatingInterval = startUpdating()
        updateButton.textContent = 'Dejar de actualizar'
    }
    updateButton.classList.toggle('stopped')
})

let updatingInterval = startUpdating()
