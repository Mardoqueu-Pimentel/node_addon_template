'use strict';

const inProduction = process.env.ENVIRONMENT === 'production';

function requireAddon(name) {

	const places = [
		`../build/lib/${name}`,
		`../build/${inProduction ? 'Release' : 'Debug'}/${name}`
	];

	for (const place of places) {
		try {
			return require(place);
		} catch (e) {}
	}

	throw new Error('could not load the module');
}

const addon = requireAddon('template');

class Klass {
	constructor(name) {
		this._addonInstance = new addon.Klass(name);
	}
	greet(name) {
		return this._addonInstance.greet(name);
	}
}

module.exports = Klass;